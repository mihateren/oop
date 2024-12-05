#pragma once

#include "Mobs/NPC.hpp"
class BattleVisitor;

class Orc : public NPC
{
private:
    int health;
    int attackDistance;
    int attackPower;
    int moveDistance;
    Point position;

public:
    Orc(int health = 100, int moveDistance = 20, int attackDistance = 10, int attackPower = 40, int x = 0, int y = 0)
        : health(health), attackDistance(attackDistance), moveDistance(moveDistance), attackPower(attackPower), position(x, y) {}

    void accept(BattleVisitor &battleVisitor, const NPC &attacker) override;

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getMoveDistance() const override { return moveDistance; }
    int getAttackPower() const override { return attackPower; }
    int getAttackDistance() const override { return attackDistance; }
    const Point &getPosition() const override { return position; }
    void setPosition(int x, int y) override { position = Point(x, y); }
    void move(Battlefield *battlefield) override;
    const char *getType() const override { return "Orc"; }
};