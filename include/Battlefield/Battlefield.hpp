#pragma once
#include "Point.hpp"
#include "../NPC.hpp"
#include "../BattleVisitor.hpp"
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>

class Battlefield
{
private:
    std::vector<std::vector<std::shared_ptr<NPC>>> field;

public:
    Battlefield() : field(500, std::vector<std::shared_ptr<NPC>>(500, nullptr)) {}

    void placeNPC(std::shared_ptr<NPC> npc);

    std::shared_ptr<NPC> getNPC(int x, int y) const;

    void removeNPC(int x, int y);

    void startBattle(BattleVisitor &battleVisitor);

    void print() const;

private:
    void attackNPCs(BattleVisitor &battleVisitor);
    void checkDeadNPCs();
    bool isBattleEnd(BattleVisitor &battleVisitor);
    void findTargets(std::shared_ptr<NPC> npc, BattleVisitor &battleVisitor, std::vector<std::shared_ptr<NPC>> &targets);
};