#include "GameController.hpp"
#include <iostream>

GameController::GameController(LogManager &logManager, Battlefield &battlefield)
    : logger(logManager), battlefield(battlefield)
{
}

void GameController::startGame(BattleVisitor &battleVisitor)
{
    logger.notifyGameStart(battlefield);
    updateGame(battleVisitor);
}

void GameController::updateGame(BattleVisitor &battleVisitor)
{
    bool battleContinues = true;
    int turnCount = 1;

    while (battleContinues)
    {
        logger.notifyTurnStart(turnCount);

        attackNPCs(battleVisitor);
        checkDeadNPCs();

        battleContinues = !isBattleEnd(battleVisitor);

        turnCount++;
    }
}

void GameController::endGame()
{
    logger.notifyGameEnd();
}

void GameController::attackNPCs(BattleVisitor &battleVisitor)
{
    std::vector<std::shared_ptr<NPC>> aliveNPCs;
    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = battlefield.getNPC(x, y);
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
        battlefield.findTargets(npc, battleVisitor, targets);

        auto it = targets.begin();
        while (it != targets.end())
        {
            if (!(*it) || (*it)->getHP() <= 0)
            {
                it = targets.erase(it);
            }
            else
            {
                ++it;
            }
        }

        if (!targets.empty())
        {
            for (auto &target : targets)
            {
                if (!target)
                    continue;
                target->accept(battleVisitor, *npc);

                logger.notifyDamageReceived(*target, npc->getAttackPower(), *npc);
            }
        }
    }
}

void GameController::checkDeadNPCs()
{
    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = battlefield.getNPC(x, y);
            if (npc && npc->getHP() <= 0)
            {
                logger.notifyDead(*npc);
                battlefield.removeNPC(x, y);
                npc.reset();
            }
        }
    }
}

bool GameController::isBattleEnd(BattleVisitor &battleVisitor)
{
    int aliveCount = 0;
    bool canAttack = false;

    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = battlefield.getNPC(x, y);
            if (npc && npc->getHP() > 0)
            {
                ++aliveCount;

                std::vector<std::shared_ptr<NPC>> targets;
                battlefield.findTargets(npc, battleVisitor, targets);
                if (!targets.empty())
                {
                    canAttack = true;
                }
            }
        }
    }

    if (aliveCount <= 1 || !canAttack)
    {
        if (aliveCount == 1)
        {
            auto npc = battlefield.getNPC(0, 0);
            if (npc)
                logger.notifyDead(*npc);
        }
        return true;
    }

    return false;
}
