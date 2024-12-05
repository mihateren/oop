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

        // moveNPCs(battlefield);

        std::this_thread::sleep_for(std::chrono::seconds(1));
        battleContinues = !isBattleEnd(battleVisitor);
        turnCount++;
    }

    isRunning = false;
    displayThread.join();

    endGame();
}

void GameController::displayMapPeriodically(std::atomic<bool> &isRunning)
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

void GameController::moveNPCs(Battlefield *battlefield)
{
    std::lock_guard<std::shared_mutex> lock(battlefieldMutex);
    for (int x = 0; x < battlefield->getFieldSize(); ++x)
    {
        for (int y = 0; y < battlefield->getFieldSize(); ++y)
        {
            auto npc = battlefield->getNPC(x, y);
            if (npc && npc->getHP() > 0)
            {
                npc->move(battlefield);
            }
        }
    }
}

void GameController::attackNPCs(BattleVisitor &battleVisitor)
{
    std::vector<std::shared_ptr<NPC>> aliveNPCs;
    for (int x = 0; x < battlefield->getFieldSize(); ++x)
    {
        for (int y = 0; y < battlefield->getFieldSize(); ++y)
        {
            auto npc = battlefield->getNPC(x, y);
            if (npc && npc->getHP() > 0)
            {
                aliveNPCs.push_back(npc);
            }
        }
    }

    for (auto &npc : aliveNPCs)
    {
        if (!npc)
            continue;
        std::vector<std::shared_ptr<NPC>> targets;
        battlefield->findTargets(npc, battleVisitor, targets);

        if (!targets.empty())
        {
            for (auto &target : targets)
            {
                if (!target || target->getHP() <= 0)
                    continue;
                target->accept(battleVisitor, *npc);

                if (logger)
                {
                    logger->notifyDamageReceived(*target, npc->getAttackPower(), *npc);
                }
            }
        }
    }
}

void GameController::checkDeadNPCs()
{
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
                battlefield->removeNPC(x, y);
                npc.reset();
            }
        }
    }
}

bool GameController::isBattleEnd(BattleVisitor &battleVisitor)
{
    int aliveCount = 0;
    bool canAttack = false;

    for (int x = 0; x < battlefield->getFieldSize(); ++x)
    {
        for (int y = 0; y < battlefield->getFieldSize(); ++y)
        {
            auto npc = battlefield->getNPC(x, y);
            if (npc && npc->getHP() > 0)
            {
                ++aliveCount;

                std::vector<std::shared_ptr<NPC>> targets;
                battlefield->findTargets(npc, battleVisitor, targets);
                if (!targets.empty())
                {
                    canAttack = true;
                }
            }
        }
    }

    return !canAttack;
}

void GameController::endGame()
{
    if (logger)
    {
        logger->notifyGameEnd();
    }
}