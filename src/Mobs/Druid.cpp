#include "../../include/Mobs/Druid.hpp"
#include "../../include/Mobs/Visitors/BattleVisitor.hpp"

void Druid::accept(BattleVisitor &battleVisitor, const NPC &attacker)
{
    battleVisitor.visit(attacker, *this);
}