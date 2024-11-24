#pragma once

#include "Listener.hpp"
#include "Battlefield/Battlefield.hpp"
#include <fstream>
#include <iostream>

class FileListener : public Listener
{
private:
    std::ofstream logFile;

public:
    FileListener();
    ~FileListener();

    void onDamageReceived(const NPC &defender, int damage, const NPC &attacker) override;
    void onDead(const NPC &npc) override;
    void onGameStart(Battlefield &battlefield) override;
    void onTurnStart(int turn) override;
    void onGameEnd() override;
};