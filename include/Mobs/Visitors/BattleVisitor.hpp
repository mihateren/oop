#pragma once

#include "Visitor.hpp"
#include "../NPC.hpp"
#include "../Orc.hpp"
#include "../Squirrel.hpp"
#include "../include/Mobs/Druid.hpp"
#include <cstring>
#include <iostream>

class BattleVisitor : public Visitor
{
public:
    void visit(const NPC &attacker, Orc &orc) override;
    void visit(const NPC &attacker, Squirrel &squirrel) override;
    void visit(const NPC &attacker, Druid &druid) override;

private:
    void attack(const NPC &attacker, NPC &defender) const;
};
