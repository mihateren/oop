#pragma once

#include <list>
#include <memory>
#include "Listener.hpp"

class NPC;
class Battlefield;

class LogManager
{
private:
    std::list<std::shared_ptr<Listener>> listeners;

public:
    void addListener(std::shared_ptr<Listener> listener);
    void removeListener(std::shared_ptr<Listener> listener);

    void notifyGameStart(Battlefield &battlefield);
    void notifyTurnStart(int turn);
    void notifyDamageReceived(const NPC &defender, int damage, const NPC &attacker);
    void notifyDead(const NPC &npc);
    void notifyGameEnd();
};