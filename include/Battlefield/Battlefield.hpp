#pragma once

#include <memory>
#include <vector>
#include "Mobs/NPC.hpp"

class Battlefield
{
private:
    std::shared_ptr<NPC> field[100][100];

public:
    Battlefield();
    ~Battlefield();

    std::shared_ptr<NPC> (&getField())[100][100];

    void placeNPC(std::shared_ptr<NPC> npc);
    void removeNPC(int x, int y);
    std::shared_ptr<NPC> getNPC(int x, int y) const;
    int getFieldSize() const { return 100; }

    void findTargets(std::shared_ptr<NPC> npc, BattleVisitor &battleVisitor, std::vector<std::shared_ptr<NPC>> &targets);
};
