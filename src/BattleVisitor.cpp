#include "../include/BattleVisitor.hpp"

void BattleVisitor::visit(const Orc &orc)
{
    std::cout << "Орк атакует!" << std::endl;
}

void BattleVisitor::visit(const Squirrel &squirrel)
{
    std::cout << "Белка моргает в шоке!" << std::endl;
}

void BattleVisitor::visit(const Druid &druid)
{
    std::cout << "Друид атакует!" << std::endl;
}