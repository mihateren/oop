#pragma once

#include <memory>
#include <vector>
#include "Battlefield/Battlefield.hpp"
#include "Logger/LogManager.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"
#include "NPCFactory.hpp"

class GameController
{
private:
    Battlefield *battlefield;
    LogManager *logger;

public:
    GameController(Battlefield &battlefield);
    GameController(LogManager &logManager, Battlefield &battlefield);
    void fillRandomNPCs(Battlefield &battlefield);
    void startGame(BattleVisitor &battleVisitor);

private:
    void updateGame(BattleVisitor &battleVisitor);
    void attackNPCs(BattleVisitor &battleVisitor);
    void moveNPCs(Battlefield *battlefield);
    void checkDeadNPCs();
    bool isBattleEnd(BattleVisitor &battleVisitor);
    void endGame();
};
