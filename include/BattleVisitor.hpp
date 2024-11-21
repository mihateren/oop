#pragma once

#include "Visitor.hpp"
#include "NPC.hpp"

class BattleVisitor : public Visitor
{
public:
    BattleVisitor() {}

    ~BattleVisitor() {}

    void visit(const Orc &orc) override;

    void visit(const Squirrel &squirrel) override;

    void visit(const Druid &druid) override;

    void attack(const NPC &attacker, NPC &defender) const
    {
        int attackerPower = attacker.getAttackPower();
        int defenderHP = defender.getHP();

        int damage = attackerPower;

        defender.setHP(defenderHP - damage);

        std::cout << "Атакующий нанес " << damage << " урона!" << std::endl;
        std::cout << "Здоровье защищающегося: " << defender.getHP() << std::endl;
    }
};