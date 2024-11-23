#include "../../include/Battlefield/Battlefield.hpp"

Battlefield::Battlefield()
{
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            field[i][j] = nullptr;
        }
    }
}

std::shared_ptr<NPC> (&Battlefield::getField())[500][500]
{
    return field;
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
            auto target = getNPC(nx, ny);
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