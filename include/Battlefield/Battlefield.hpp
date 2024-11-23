#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "../NPC.hpp"
#include "../BattleVisitor.hpp"
#include "../Observer/NotificationManager.hpp"

class Battlefield
{
public:
    Battlefield(NotificationManager &notificationManager);
    void placeNPC(std::shared_ptr<NPC> npc);
    std::shared_ptr<NPC> getNPC(int x, int y) const;
    void removeNPC(int x, int y);
    void print() const;
    void startBattle(BattleVisitor &battleVisitor);
    void receiveDamage(const NPC &attacker, NPC &defender, int damage);

private:
    void attackNPCs(BattleVisitor &battleVisitor);
    void findTargets(std::shared_ptr<NPC> npc, BattleVisitor &battleVisitor, std::vector<std::shared_ptr<NPC>> &targets);
    void checkDeadNPCs();
    bool isBattleEnd(BattleVisitor &battleVisitor);

    std::shared_ptr<NPC> field[500][500];
    NotificationManager &notificationManager;
};