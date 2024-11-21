#pragma once

#include "../NPC.hpp"
#include "../BattleVisitor.hpp"

class Druid : public NPC
{
private:
    int health;
    int attackDistance;
    int attackPower;

public:
    Druid(int health = 80, int attackDistance = 10, int attackPower = 30) : health(health), attackDistance(attackDistance), attackPower(attackPower) {};

    void accept(BattleVisitor &battleVisitor, const NPC &attacker) override
    {
        battleVisitor.visit(attacker, *this);
    }

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getAttackPower() const override { return attackPower; }
    int getAttackDistance() const { return attackDistance; }
    const char *getType() const override { return "Друид"; }
};