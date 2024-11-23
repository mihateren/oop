#include "../../include/Mobs/Squirrel.hpp"
#include "../../include/Mobs/Visitors/BattleVisitor.hpp"

void Squirrel::accept(BattleVisitor &battleVisitor, const NPC &attacker)
{
    battleVisitor.visit(attacker, *this);
}