#pragma once

class Orc;
class Squirrel;
class Druid;
class NPC;

#include "Visitor.hpp"

class BattleVisitor : public Visitor
{
public:
    void visit(const NPC &attacker, Orc &orc) override;
    void visit(const NPC &attacker, Squirrel &squirrel) override;
    void visit(const NPC &attacker, Druid &druid) override;

private:
    void attack(const NPC &attacker, NPC &defender) const;
};
