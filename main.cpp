#include "include/Mobs/Visitors/BattleVisitor.hpp"
#include "include/NPCFactory.hpp"
#include "include/Battlefield/Battlefield.hpp"
#include "include/Logger/ConsoleListener.hpp"
#include "include/Logger/LogManager.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>

int main()
{
    LogManager LogManager;
    std::shared_ptr<Listener> consoleListener = std::make_shared<ConsoleListener>();

    LogManager.addListener(consoleListener);

    NPCFactory fabric;
    BattleVisitor battleVisitor;
    Battlefield battlefield(LogManager);

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