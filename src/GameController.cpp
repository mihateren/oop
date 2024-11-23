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
        attackNPCs(battleVisitor);

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
    int turn = 1;

    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = battlefield.getNPC(x, y);
            if (npc && npc->getHP() > 0)
            {
                logger.notifyTurnStart(turn++);

                std::vector<std::shared_ptr<NPC>> targets;
                battlefield.findTargets(npc, battleVisitor, targets);

                for (auto it = targets.begin(); it != targets.end();)
                {
                    if ((*it)->getHP() <= 0)
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
                        npc->accept(battleVisitor, *target);

                        logger.notifyDamageReceived(*target, npc->getAttackPower(), *npc);

                        if (target->getHP() <= 0)
                        {
                            logger.notifyDead(*target);
                            battlefield.removeNPC(target->getPosition().x, target->getPosition().y);
                        }
                    }
                }
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
            logger.notifyDead(*battlefield.getNPC(0, 0));
        }
        return true;
    }

    return false;
}
