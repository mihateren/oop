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
    for (int count = 0; count < 50; count++)
    {
        int x, y;
        do
        {
            x = rand() % battlefield.getFieldSize();
            y = rand() % battlefield.getFieldSize();
        } while (battlefield.getNPC(x, y) != nullptr);
        NPCType randType = npcTypes[rand() % 3];
        std::shared_ptr<NPC> npc = npcFactory.createNPC(randType, x, y);
        battlefield.placeNPC(npc);
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

        battleContinues = !isBattleEnd(battleVisitor);

        turnCount++;
    }
}

void GameController::endGame()
{
    if (logger)
    {
        logger->notifyGameEnd();
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
