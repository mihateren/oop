#include "Mobs/Visitors/BattleVisitor.hpp"
#include "NPCFactory.hpp"
#include "Logger/ConsoleListener.hpp"
#include "Logger/LogManager.hpp"
#include "Battlefield/Battlefield.hpp"
#include "GameController.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>

int main()
{
    LogManager logManager;
    std::shared_ptr<Listener> consoleListener = std::make_shared<ConsoleListener>();
    logManager.addListener(consoleListener);

    NPCFactory fabric;
    BattleVisitor battleVisitor;
    Battlefield battlefield;

    GameController gameController(logManager, battlefield);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int x1 = std::rand() % 10;
    int y1 = std::rand() % 10;
    int x2 = std::rand() % 10;
    int y2 = std::rand() % 10;
    int x3 = std::rand() % 10;
    int y3 = std::rand() % 10;

    auto orc = fabric.createNPC(NPCType::Orc, x1, y1);
    auto squirrel = fabric.createNPC(NPCType::Squirrel, x2, y2);
    auto druid = fabric.createNPC(NPCType::Druid, x3, y3);

    battlefield.placeNPC(orc);
    battlefield.placeNPC(squirrel);
    battlefield.placeNPC(druid);

    gameController.startGame(battleVisitor);

    gameController.endGame();

    return 0;
}
