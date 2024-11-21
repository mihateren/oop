#include "../include/BattleVisitor.hpp"
#include "../include/NPC.hpp"
#include "../include/Mobs/Orc.hpp"
#include "../include/Mobs/Squirrel.hpp"
#include "../include/Mobs/Druid.hpp"

void BattleVisitor::visit(const NPC &attacker, Orc &orc)
{
    std::cout << attacker.getType() << " атакует Орка." << std::endl;
    attack(attacker, orc);
}

void BattleVisitor::visit(const NPC &attacker, Squirrel &squirrel)
{
    std::cout << "Атакующий: " << attacker.getType() << " атакует Белку." << std::endl;
    attack(attacker, squirrel);
}

void BattleVisitor::visit(const NPC &attacker, Druid &druid)
{
    std::cout << "Атакующий: " << attacker.getType() << " атакует Друида." << std::endl;
    attack(attacker, druid);
}

void BattleVisitor::attack(const NPC &attacker, NPC &defender) const
{
    int attackerPower = attacker.getAttackPower();
    int defenderHP = defender.getHP();
    int damage = attackerPower;

    defender.setHP(defenderHP - damage);

    std::cout << "Атакующий нанес " << damage << " урона!" << std::endl;
    std::cout << "Здоровье защищающегося: " << defender.getHP() << std::endl;
}
