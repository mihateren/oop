#pragma once

#include <iostream>
#include <memory>

class BattleVisitor;

class NPC
{
public:
    virtual ~NPC() = default;
    virtual void accept(BattleVisitor &visitor) const = 0;
    virtual void battle(NPC &other) const = 0;
    virtual int getAttackPower() const = 0;
    virtual int getHP() const = 0;
    virtual void setHP(int hp) = 0;
};
