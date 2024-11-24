#pragma once

#include <memory>
#include <vector>
#include "Mobs/NPC.hpp"

class Battlefield
{
public:
    Battlefield();

    std::shared_ptr<NPC> (&getField())[500][500];

    void placeNPC(std::shared_ptr<NPC> npc);
    void removeNPC(int x, int y);
    std::shared_ptr<NPC> getNPC(int x, int y) const;

    void findTargets(std::shared_ptr<NPC> npc, BattleVisitor &battleVisitor, std::vector<std::shared_ptr<NPC>> &targets);

private:
    std::shared_ptr<NPC> field[500][500];
};
