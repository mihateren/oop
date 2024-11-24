#include "Mobs/Visitors/BattleVisitor.hpp"

void BattleVisitor::visit(const NPC &attacker, Orc &orc)
{
    attack(attacker, orc);
}

void BattleVisitor::visit(const NPC &attacker, Squirrel &squirrel)
{
    attack(attacker, squirrel);
}

void BattleVisitor::visit(const NPC &attacker, Druid &druid)
{
    attack(attacker, druid);
}

void BattleVisitor::attack(const NPC &attacker, NPC &defender) const
{

    int attackPower = attacker.getAttackPower();

    int defenderHP = defender.getHP();
    defenderHP = std::max(defenderHP - attackPower, 0);

    defender.setHP(defenderHP);
}