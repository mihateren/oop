#pragma once

#include <iostream>
#include <memory>
#include "Battlefield/Point.hpp"
class BattleVisitor;

class NPC
{
public:
    virtual ~NPC() = default;

    virtual int getHP() const = 0;
    virtual void setHP(int hp) = 0;
    virtual int getMoveDistance() const = 0;
    virtual int getAttackPower() const = 0;
    virtual int getAttackDistance() const = 0;
    virtual const char *getType() const = 0;
    virtual const Point &getPosition() const = 0;
    virtual void setPosition(int x, int y) = 0;

    virtual void accept(BattleVisitor &battleVisitor, const NPC &attacker) = 0;
};