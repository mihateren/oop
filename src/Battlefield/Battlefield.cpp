#include "../../include/Battlefield/Battlefield.hpp"
#include <cmath>

Battlefield::Battlefield(LogManager &LogManager)
    : logger(LogManager)
{
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            field[i][j] = nullptr;
        }
    }
}

void Battlefield::placeNPC(std::shared_ptr<NPC> npc)
{
    int x = npc->getPosition().x;
    int y = npc->getPosition().y;
    if (x >= 0 && x < 500 && y >= 0 && y < 500)
    {
        field[x][y] = npc;
    }
}

std::shared_ptr<NPC> Battlefield::getNPC(int x, int y) const
{
    if (x >= 0 && x < 500 && y >= 0 && y < 500)
    {
        return field[x][y];
    }
    return nullptr;
}

void Battlefield::removeNPC(int x, int y)
{
    if (x >= 0 && x < 500 && y >= 0 && y < 500)
    {
        field[x][y] = nullptr;
    }
}

void Battlefield::print() const
{
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            if (field[i][j] != nullptr)
            {
                std::cout << field[i][j]->getType();
                field[i][j]->getPosition().print();
                std::cout << std::endl;
            }
        }
    }
}

void Battlefield::startBattle(BattleVisitor &battleVisitor)
{
    logger.notifyGameStart(*this);

    bool battleContinues = true;

    while (battleContinues)
    {
        attackNPCs(battleVisitor);
        checkDeadNPCs();
        battleContinues = !isBattleEnd(battleVisitor);
    }

    logger.notifyGameEnd();
}

void Battlefield::attackNPCs(BattleVisitor &battleVisitor)
{
    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = getNPC(x, y);
            if (npc)
            {
                std::vector<std::shared_ptr<NPC>> targets;
                findTargets(npc, battleVisitor, targets);
                if (!targets.empty())
                {
                    auto it = targets.begin();
                    while (it != targets.end())
                    {
                        auto target = *it;
                        target->accept(battleVisitor, *npc);
                        if (target->getHP() <= 0)
                        {
                            logger.notifyDead(*target);
                            removeNPC(target->getPosition().x, target->getPosition().y);
                            it = targets.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
            }
        }
    }
}

void Battlefield::findTargets(std::shared_ptr<NPC> npc, BattleVisitor &battleVisitor, std::vector<std::shared_ptr<NPC>> &targets)
{
    int attackDistance = npc->getAttackDistance();
    int startX = std::max(0, npc->getPosition().x - attackDistance);
    int endX = std::min(499, npc->getPosition().x + attackDistance);
    int startY = std::max(0, npc->getPosition().y - attackDistance);
    int endY = std::min(499, npc->getPosition().y + attackDistance);

    for (int nx = startX; nx <= endX; ++nx)
    {
        for (int ny = startY; ny <= endY; ++ny)
        {
            auto target = Battlefield::getNPC(nx, ny);
            if (target && target != npc)
            {
                int dx = nx - npc->getPosition().x;
                int dy = ny - npc->getPosition().y;
                double distance = std::sqrt(dx * dx + dy * dy);
                if (distance <= attackDistance)
                {
                    targets.push_back(target);
                }
            }
        }
    }
}

void Battlefield::checkDeadNPCs()
{
    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = getNPC(x, y);
            if (npc && npc->getHP() <= 0)
            {
                logger.notifyDead(*npc);
                removeNPC(x, y);
            }
        }
    }
}

bool Battlefield::isBattleEnd(BattleVisitor &battleVisitor)
{
    std::vector<std::shared_ptr<NPC>> aliveNPCs;
    int aliveCount = 0;
    bool canAttack = false;

    for (int x = 0; x < 500; ++x)
    {
        for (int y = 0; y < 500; ++y)
        {
            auto npc = getNPC(x, y);
            if (npc)
            {
                ++aliveCount;
                aliveNPCs.push_back(npc);
            }
        }
    }

    for (const auto &npc : aliveNPCs)
    {
        std::vector<std::shared_ptr<NPC>> targets;
        findTargets(npc, battleVisitor, targets);
        if (!targets.empty())
        {
            canAttack = true;
            break;
        }
    }

    if (aliveCount == 1)
    {
        logger.notifyDead(*aliveNPCs[0]);
    }

    return aliveCount <= 1 || !canAttack;
}