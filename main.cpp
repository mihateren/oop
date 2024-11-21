#include "include/NPCFabric.hpp"
#include "include/BattleVisitor.hpp"

int main()
{
    NPCFabric fabric;
    BattleVisitor strategy;

    auto orc = fabric.createNPC(NPCType::Orc);
    auto squirrel = fabric.createNPC(NPCType::Squirrel);
    auto druid = fabric.createNPC(NPCType::Druid);

    strategy.attack(*orc, *squirrel);
    strategy.attack(*squirrel, *druid);
    strategy.attack(*druid, *orc);

    return 0;
}