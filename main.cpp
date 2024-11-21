#include "include/NPCFaсtory.hpp"
#include "include/BattleVisitor.hpp"

int main()
{
    NPCFactory fabric;
    BattleVisitor battleVisitor;

    auto orc = fabric.createNPC(NPCType::Orc);
    auto squirrel = fabric.createNPC(NPCType::Squirrel);
    auto druid = fabric.createNPC(NPCType::Druid);

    squirrel->accept(battleVisitor, *orc);

    return 0;
}