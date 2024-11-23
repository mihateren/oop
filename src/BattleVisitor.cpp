#include "../include/BattleVisitor.hpp"
#include "../include/NPC.hpp"
#include "../include/Mobs/Orc.hpp"
#include "../include/Mobs/Squirrel.hpp"
#include "../include/Mobs/Druid.hpp"
#include <cstring>

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

    if (strcmp(attacker.getType(), "Белка") == 0)
    {
        return;
    }

    int attackPower = attacker.getAttackPower();

    int defenderHP = defender.getHP();
    defenderHP = std::max(defenderHP - attackPower, 0);
    defender.setHP(defenderHP);
    std::cout << attacker.getType() << " атакует " << defender.getType() << ". Здоровье " << defender.getType() << ": " << defenderHP << std::endl;
}