#pragma once

#include <memory>
#include <vector>
#include "Battlefield/Battlefield.hpp"
#include "Logger/LogManager.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"

class GameController
{
public:
    GameController(LogManager &logManager, Battlefield &battlefield);
    void startGame(BattleVisitor &battleVisitor);
    void updateGame(BattleVisitor &battleVisitor);
    void endGame();

private:
    void attackNPCs(BattleVisitor &battleVisitor);
    void checkDeadNPCs();
    bool isBattleEnd(BattleVisitor &battleVisitor);

    Battlefield &battlefield;
    LogManager &logger;
};
