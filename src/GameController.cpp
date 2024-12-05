#include "GameController.hpp"
#include <iostream>

GameController::GameController(Battlefield &battlefield)
    : battlefield(&battlefield), logger(nullptr)
{
}

GameController::GameController(LogManager &logManager, Battlefield &battlefield)
    : logger(&logManager), battlefield(&battlefield)
{
}

void GameController::fillRandomNPCs(Battlefield &battlefield)
{
    NPCFactory npcFactory;
    NPCType npcTypes[] = {NPCType::Orc, NPCType::Squirrel, NPCType::Druid};
    std::set<std::pair<int, int>> occupiedPositions;

    int fieldSize = battlefield.getFieldSize();
    if (fieldSize * fieldSize < 50)
    {
        throw std::runtime_error("Field size is too small to place 50 NPCs.");
    }

    for (int count = 0; count < 50; count++)
    {
        int x, y;
        do
        {
            x = rand() % fieldSize;
            y = rand() % fieldSize;
        } while (occupiedPositions.find({x, y}) != occupiedPositions.end());

        occupiedPositions.insert({x, y});
        NPCType randType = npcTypes[rand() % 3];
        std::shared_ptr<NPC> npc = npcFactory.createNPC(randType, x, y);
        battlefield.placeNPC(npc, x, y);
    }
}

void GameController::startGame(BattleVisitor &battleVisitor)
{
    if (logger)
    {
        logger->notifyGameStart(*battlefield);
    }
    updateGame(battleVisitor);
}

void GameController::updateGame(BattleVisitor &battleVisitor)
{
    std::atomic<bool> isRunning(true);

    std::thread displayThread(&GameController::displayMapPeriodically, this, std::ref(isRunning));
    std::thread movementThread(&GameController::moveNPCsPeriodically, this, std::ref(isRunning));

    bool battleContinues = true;
    int turnCount = 1;

    while (battleContinues)
    {
        if (logger)
        {
            logger->notifyTurnStart(turnCount);
        }

        attackNPCs(battleVisitor);
        checkDeadNPCs();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        battleContinues = !isBattleEnd(battleVisitor);
        turnCount++;
    }

    isRunning = false;

    movementThread.join();
    displayThread.join();
    endGame();
    std::cerr << "updateGame: endGame() completed\n";
}

void GameController::moveNPCsPeriodically(std::atomic<bool> &isRunning)
{
    try
    {
        while (isRunning)
        {
            {
                std::lock_guard<std::shared_mutex> lock(battlefieldMutex);
                moveNPCs(this->battlefield);
            }

            {
                std::shared_lock<std::shared_mutex> lock(battlefieldMutex);
                detectBattles();
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in moveNPCsPeriodically: " << e.what() << std::endl;
        isRunning = false;
    }
}

void GameController::displayMapPeriodically(std::atomic<bool> &isRunning)
{
    try
    {
        while (isRunning)
        {
            {
                std::shared_lock<std::shared_mutex> lock(battlefieldMutex);
                battlefield->print();
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in displayMapPeriodically: " << e.what() << std::endl;
        isRunning = false;
    }
}

void GameController::moveNPCs(Battlefield *battlefield)
{
    std::vector<std::shared_ptr<NPC>> npcsToMove = battlefield->getAllNPCs();

    for (auto &npc : npcsToMove)
    {
        npc->move(battlefield);
    }
}

void GameController::detectBattles()
{
    std::vector<std::shared_ptr<NPC>> npcs = battlefield->getAllNPCs();

    for (auto &npc : npcs)
    {
        if (!npc)
            continue;

        std::shared_lock<std::shared_mutex> npcLock(npc->getMutex());
        if (npc->getHP() <= 0)
            continue;

        std::vector<std::shared_ptr<NPC>> targets;
        battlefield->findTargets(npc, targets);

        for (auto &target : targets)
        {
            if (!target)
                continue;

            std::shared_lock<std::shared_mutex> targetLock(target->getMutex());
            if (target->getHP() <= 0)
                continue;

            if (npc != target)
            {
                std::lock_guard<std::mutex> lock(battleTasksMutex);
                battleTasks.emplace_back(npc, target);
            }
        }
    }
}

void GameController::attackNPCs(BattleVisitor &battleVisitor)
{
    std::vector<std::shared_ptr<NPC>> aliveNPCs;
    {
        std::shared_lock<std::shared_mutex> lock(battlefieldMutex);
        aliveNPCs = battlefield->getAllNPCs();
    }

    for (auto &npc : aliveNPCs)
    {
        if (!npc)
        {
            continue;
        }

        std::shared_lock<std::shared_mutex> npcLock(npc->getMutex());
        if (npc->getHP() <= 0)
        {
            continue;
        }

        std::vector<std::shared_ptr<NPC>> targets;
        {
            std::shared_lock<std::shared_mutex> lock(battlefieldMutex);
            battlefield->findTargets(npc, targets);
        }

        for (auto &target : targets)
        {
            if (!target)
            {
                continue;
            }

            std::shared_lock<std::shared_mutex> targetLock(target->getMutex());
            if (target->getHP() <= 0)
            {
                continue;
            }

            try
            {
                target->accept(battleVisitor, *npc);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Exception during attackNPCs: " << e.what() << std::endl;
            }

            if (logger)
            {
                logger->notifyDamageReceived(*target, npc->getAttackPower(), *npc);
            }
        }
    }
}

void GameController::checkDeadNPCs()
{
    std::vector<std::pair<int, int>> positionsToRemove;

    for (int x = 0; x < battlefield->getFieldSize(); ++x)
    {
        for (int y = 0; y < battlefield->getFieldSize(); ++y)
        {
            auto npc = battlefield->getNPC(x, y);
            if (npc && npc->getHP() <= 0)
            {
                if (logger)
                {
                    logger->notifyDead(*npc);
                }
                positionsToRemove.emplace_back(x, y);
            }
        }
    }

    for (const auto &pos : positionsToRemove)
    {
        battlefield->removeNPC(pos.first, pos.second);
    }
}

bool GameController::isBattleEnd(BattleVisitor &battleVisitor)
{
    int aliveCount = 0;

    for (int x = 0; x < battlefield->getFieldSize(); ++x)
    {
        for (int y = 0; y < battlefield->getFieldSize(); ++y)
        {
            auto npc = battlefield->getNPC(x, y);
            if (npc && npc->getHP() > 0)
            {
                ++aliveCount;
                if (aliveCount > 1)
                {
                    return false;
                }
            }
        }
    }

    return (aliveCount <= 1);
}

void GameController::endGame()
{
    battlefield->print();
    if (logger)
    {
        logger->notifyGameEnd();
    }
}