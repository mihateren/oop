#pragma once

#include "Mobs/NPC.hpp"
class BattleVisitor;

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

    void accept(BattleVisitor &battleVisitor, const NPC &attacker) override;

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getAttackPower() const override { return attackPower; }
    int getAttackDistance() const override { return attackDistance; }
    const Point &getPosition() const override { return position; }
    const char *getType() const override { return "Орк"; }
};