#pragma once

#include "NPC.hpp"

class Orc;
class Squirrel;
class Druid;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(const Orc &orc) = 0;
    virtual void visit(const Squirrel &squirrel) = 0;
    virtual void visit(const Druid &druid) = 0;
};
