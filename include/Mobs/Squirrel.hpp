#pragma once

#include "../NPC.hpp"
#include "../BattleVisitor.hpp"

class Squirrel : public NPC
{
private:
    int health;
    int attackDistance;
    int attackPower;

public:
    Squirrel(int health = 10, int attackDistance = 1, int attackPower = 0) : health(health), attackDistance(attackDistance), attackPower(attackPower) {};

    void accept(BattleVisitor &battleVisitor, const NPC &attacker) override
    {
        battleVisitor.visit(attacker, *this);
    }

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getAttackPower() const override { return attackPower; }
    int getAttackDistance() const { return attackDistance; }
    const char *getType() const override { return "Белка"; }
};