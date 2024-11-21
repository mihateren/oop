#pragma once

#include "../NPC.hpp"
#include "../BattleVisitor.hpp"

class Orc : public NPC
{
private:
    int health;
    int attackDistance;
    int attackPower;

public:
    Orc(int health = 100, int attackDistance = 5, int attackPower = 40) : health(health), attackDistance(attackDistance), attackPower(attackPower) {};

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
    int getAttackPower() const  override { return attackPower; }
    int getAttackDistance() const { return attackDistance; }
};