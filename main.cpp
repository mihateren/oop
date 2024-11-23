#include "include/NPCFactory.hpp"
#include "include/BattleVisitor.hpp"
#include "include/Battlefield/Battlefield.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>

int main()
{
    system("chcp 65001");
    NPCFactory fabric;
    BattleVisitor battleVisitor;
    Battlefield battlefield;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int x1 = std::rand() % 20;
    int y1 = std::rand() % 20;
    int x2 = std::rand() % 20;
    int y2 = std::rand() % 20;
    int x3 = std::rand() % 20;
    int y3 = std::rand() % 20;

    auto orc = fabric.createNPC(NPCType::Orc, x1, y1);
    auto squirrel = fabric.createNPC(NPCType::Squirrel, x2, y2);
    auto druid = fabric.createNPC(NPCType::Druid, x3, y3);

    battlefield.placeNPC(orc);
    battlefield.placeNPC(squirrel);
    battlefield.placeNPC(druid);

    battlefield.print();

    battlefield.startBattle(battleVisitor);

    return 0;
}