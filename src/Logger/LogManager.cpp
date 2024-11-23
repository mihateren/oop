#include "../../include/Logger/LogManager.hpp"

void LogManager::addListener(std::shared_ptr<Listener> listener) { listeners.push_back(listener); }

void LogManager::removeListener(std::shared_ptr<Listener> listener) { listeners.remove(listener); }

void LogManager::notifyGameStart(Battlefield &battlefield)
{
    for (auto &listener : listeners)
    {
        listener->onGameStart(battlefield);
    }
}

void LogManager::notifyDamageReceived(const NPC &defender, int damage, const NPC &attacker)
{
    for (auto &listener : listeners)
    {
        listener->onDamageReceived(defender, damage, attacker);
    }
}

void LogManager::notifyDead(const NPC &npc)
{
    for (auto &listener : listeners)
    {
        listener->onDead(npc);
    }
}

void LogManager::notifyTurnStart(int turn)
{
    for (auto &listener : listeners)
    {
        listener->onTurnStart(turn);
    }
}

void LogManager::notifyGameEnd()
{
    for (auto &listener : listeners)
    {
        listener->onGameEnd();
    }
}