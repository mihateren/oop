#include "../../include/Mobs/Orc.hpp"
#include "../../include/Mobs/Visitors/BattleVisitor.hpp"

void Orc::accept(BattleVisitor &battleVisitor, const NPC &attacker)
{
    battleVisitor.visit(attacker, *this);
}