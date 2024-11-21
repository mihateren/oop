#pragma once

#include <iostream>
#include <memory>
class BattleVisitor;

class NPC
{
public:
    virtual ~NPC() = default;

    virtual int getHP() const = 0;
    virtual void setHP(int hp) = 0;
    virtual int getAttackPower() const = 0;
    virtual const char *getType() const = 0;

    virtual void accept(BattleVisitor &battleVisitor, const NPC &attacker) = 0;
};
