#pragma once

#include "../NPC.hpp"
#include "../BattleVisitor.hpp"

class Orc : public NPC
{
private:
    int health;
    int attackDistance;
    int attackPower;
    Point position;

public:
    Orc(int health = 100, int attackDistance = 5, int attackPower = 40, int x = 0, int y = 0)
        : health(health), attackDistance(attackDistance), attackPower(attackPower), position(x, y) {}

    void accept(BattleVisitor &battleVisitor, const NPC &attacker) override
    {
        battleVisitor.visit(attacker, *this);
    }

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getAttackPower() const override { return attackPower; }
    const char *getType() const override { return "Орк"; }
};
