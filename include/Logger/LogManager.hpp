#pragma once

#include <list>
#include <memory>
#include "Listener.hpp"

class NPC;
class Battlefield;

class LogManager
{
public:
    void addListener(std::shared_ptr<Listener> listener) { listeners.push_back(listener); }
    void removeListener(std::shared_ptr<Listener> listener) { listeners.remove(listener); }

    void notifyGameStart(const Battlefield &battlefield)
    {
        for (auto &listener : listeners)
        {
            listener->onGameStart(battlefield);
        }
    }

    void notifyGameEnd()
    {
        for (auto &listener : listeners)
        {
            listener->onGameEnd();
        }
    }

    void notifyDamageReceived(const NPC &defender, int damage, const NPC &attacker)
    {
        for (auto &listener : listeners)
        {
            listener->onDamageReceived(defender, damage, attacker);
        }
    }

    void notifyDead(const NPC &npc)
    {
        for (auto &listener : listeners)
        {
            listener->onDead(npc);
        }
    }

private:
    std::list<std::shared_ptr<Listener>> listeners;
};