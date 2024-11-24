#pragma once

#include "Listener.hpp"
#include "Battlefield/Battlefield.hpp"
#include <iostream>

class ConsoleListener : public Listener
{
    void onDamageReceived(const NPC &defender, int damage, const NPC &attacker) override;

    void onDead(const NPC &npc) override;

    void onGameStart(Battlefield &battlefield) override;
    void onTurnStart(int turn) override;
    void onGameEnd() override;
};