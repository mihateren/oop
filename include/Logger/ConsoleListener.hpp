#pragma once

#include "Listener.hpp"
#include <iostream>

class ConsoleListener : public Listener
{
    void onDamageReceived(const NPC &defender, int damage, const NPC &attacker) override
    {
        std::cout << defender.getType() << " получает " << damage << " урона от " << attacker.getType() << ".\n";
    }

    void onDead(const NPC &npc) override
    {
        std::cout << npc.getType() << " умер.\n";
    }

    void onGameStart(const Battlefield &battlefield) override
    {
        std::cout << "Бой начался!\n";
        battlefield.print();
    }

    void onGameEnd() override
    {
        std::cout << "Бой завершён!\n";
    }
};