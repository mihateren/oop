#pragma once

#include <memory>
#include <vector>
#include "Mobs/NPC.hpp"

class Battlefield
{
private:
    static constexpr int fieldSize = 50;
    std::shared_ptr<NPC> field[fieldSize][fieldSize];

public:
    Battlefield();
    ~Battlefield();

    std::shared_ptr<NPC> (&getField())[fieldSize][fieldSize];

    void placeNPC(std::shared_ptr<NPC> npc, int x, int y);
    void removeNPC(int x, int y);
    std::shared_ptr<NPC> getNPC(int x, int y) const;
    int getFieldSize() const { return fieldSize; }
    void print() const;

    void findTargets(std::shared_ptr<NPC> npc, BattleVisitor &battleVisitor, std::vector<std::shared_ptr<NPC>> &targets);
};
