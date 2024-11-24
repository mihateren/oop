#include "Mobs/Druid.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"

void Druid::accept(BattleVisitor &battleVisitor, const NPC &attacker)
{
    battleVisitor.visit(attacker, *this);
}