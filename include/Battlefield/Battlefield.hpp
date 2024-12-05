#pragma once

#include <memory>
#include <vector>
#include "Mobs/NPC.hpp"
#include <shared_mutex>

class Battlefield
{
private:
    static constexpr int fieldSize = 50;
    std::shared_ptr<NPC> field[fieldSize][fieldSize];
    mutable std::shared_mutex fieldMutex;

public:
    Battlefield();
    ~Battlefield();

    std::shared_ptr<NPC> (&getField())[fieldSize][fieldSize];

    void placeNPC(std::shared_ptr<NPC> npc, int x, int y);
    void removeNPC(int x, int y);
    std::shared_ptr<NPC> getNPC(int x, int y) const;
    int getFieldSize() const { return fieldSize; }
    void print() const;

    std::shared_mutex &getMutex() { return fieldMutex; }

    void findTargets(std::shared_ptr<NPC> npc, std::vector<std::shared_ptr<NPC>> &targets);
    std::vector<std::shared_ptr<NPC>> getAllNPCs() const;
};
