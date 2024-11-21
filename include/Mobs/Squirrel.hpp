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

    void accept(BattleVisitor &visitor) const override
    {
        visitor.visit(*this);
    }

    void battle(NPC &other) const override
    {
        BattleVisitor visitor;
        other.accept(visitor);
    }

    int getHP() const override { return health; }
    void setHP(int hp) override { health = hp; }
    int getAttackPower() const override { return attackPower; }
    int getAttackDistance() const { return attackDistance; }
};