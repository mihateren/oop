#pragma once

#include <iostream>
#include <memory>
#include "Battlefield/Point.hpp"
#include <vector>
#include <shared_mutex>
#include <memory>

class BattleVisitor;
class Battlefield;

class NPC : public std::enable_shared_from_this<NPC>
{
private:
    mutable std::shared_mutex npcMutex;

public:
    virtual ~NPC() = default;
    std::shared_ptr<NPC> shared_from_this()
    {
        return std::enable_shared_from_this<NPC>::shared_from_this();
    }

    std::shared_ptr<NPC const> shared_from_this() const
    {
        return std::enable_shared_from_this<NPC>::shared_from_this();
    }

    std::shared_mutex &getMutex() { return npcMutex; }

    virtual int getHP() const = 0;
    virtual void setHP(int hp) = 0;
    virtual int getMoveDistance() const = 0;
    virtual int getAttackPower() const = 0;
    virtual int getAttackDistance() const = 0;
    virtual const char *getType() const = 0;
    virtual const Point &getPosition() const = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void move(Battlefield *battlefield) = 0;

    virtual void accept(BattleVisitor &battleVisitor, const NPC &attacker) = 0;
};