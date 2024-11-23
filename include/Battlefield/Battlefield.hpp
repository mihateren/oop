#pragma once
#include "Point.hpp"
#include "../NPC.hpp"
#include <vector>
#include <memory>

class Battlefield
{
private:
    std::vector<std::vector<std::shared_ptr<NPC>>> field;

public:
    Battlefield() : field(500, std::vector<std::shared_ptr<NPC>>(500, nullptr)) {}

    void placeNPC(int x, int y, std::shared_ptr<NPC> npc)
    {
        if (x >= 0 && x < 500 && y >= 0 && y < 500)
        {
            field[x][y] = npc;
        }
    }

    std::shared_ptr<NPC> getNPC(int x, int y) const
    {
        if (x >= 0 && x < 500 && y >= 0 && y < 500)
        {
            return field[x][y];
        }
        return nullptr;
    }

    void removeNPC(int x, int y)
    {
        if (x >= 0 && x < 500 && y >= 0 && y < 500)
        {
            field[x][y] = nullptr;
        }
    }
};