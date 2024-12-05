#pragma once

#include <memory>
#include <vector>
#include "Battlefield/Battlefield.hpp"
#include "Logger/LogManager.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"
#include "NPCFactory.hpp"
#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <set>
#include <utility>

class GameController
{
private:
    Battlefield *battlefield;
    LogManager *logger;
    std::shared_mutex battlefieldMutex;

public:
    GameController(Battlefield &battlefield);
    GameController(LogManager &logManager, Battlefield &battlefield);
    void fillRandomNPCs(Battlefield &battlefield);
    void startGame(BattleVisitor &battleVisitor);

private:
    void updateGame(BattleVisitor &battleVisitor);
    void displayMapPeriodically(std::atomic<bool> &isRunning);
    void attackNPCs(BattleVisitor &battleVisitor);
    void moveNPCs(Battlefield *battlefield);
    void checkDeadNPCs();
    bool isBattleEnd(BattleVisitor &battleVisitor);
    void endGame();
};
