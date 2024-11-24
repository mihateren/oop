#include "Mobs/Visitors/BattleVisitor.hpp"
#include "NPCFactory.hpp"
#include "Logger/ConsoleListener.hpp"
#include "Logger/LogManager.hpp"
#include "Logger/FileListener.hpp"
#include "Battlefield/Battlefield.hpp"
#include "GameController.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    LogManager logManager;
    std::shared_ptr<Listener> consoleListener = std::make_shared<ConsoleListener>();
    std::shared_ptr<Listener> fileListener = std::make_shared<FileListener>();
    logManager.addListener(fileListener);

    NPCFactory fabric;
    BattleVisitor battleVisitor;
    Battlefield battlefield;

    GameController gameController(logManager, battlefield);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try
    {
        std::vector<std::shared_ptr<NPC>> npcs = fabric.createNPCFromFile("npcs.txt");

        for (const auto &npc : npcs)
        {
            battlefield.placeNPC(npc);
        }

        gameController.startGame(battleVisitor);

        gameController.endGame();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
