#pragma once

class NPC;
class Orc;
class Squirrel;
class Druid;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(const NPC &attacker, Orc &orc) = 0;
    virtual void visit(const NPC &attacker, Squirrel &squirrel) = 0;
    virtual void visit(const NPC &attacker, Druid &druid) = 0;
};
