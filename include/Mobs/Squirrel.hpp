#pragma once

#include "NPC.hpp"

#include "./Visitors/BattleVisitor.hpp"

class Squirrel : public NPC
{
private:
    int health;
    int attackDistance;
    int attackPower;
    Point position;

public:
    Squirrel(int health = 10, int attackDistance = 1, int attackPower = 0, int x = 0, int y = 0) : health(health), attackDistance(attackDistance), attackPower(attackPower), position(x, y) {};

    void accept(BattleVisitor &battleVisitor, const NPC &attacker) override;

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getAttackPower() const override { return attackPower; }
    int getAttackDistance() const override { return attackDistance; }
    const Point &getPosition() const override { return position; }
    const char *getType() const override { return "Белка"; }
};