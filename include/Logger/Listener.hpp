#pragma once

class NPC;
class Battlefield;

class Listener
{
public:
    virtual void onDamageReceived(const NPC &defender, int damage, const NPC &attacker) = 0;
    virtual void onDead(const NPC &npc) = 0;
    virtual void onGameStart(Battlefield &battlefield) = 0;
    virtual void onTurnStart(int turn) = 0;
    virtual void onGameEnd() = 0;
    virtual ~Listener() = default;
};
