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
#include <deque>

class GameController
{
private:
    Battlefield *battlefield;
    LogManager *logger;
    std::shared_mutex battlefieldMutex;
    std::deque<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> battleTasks;
    std::mutex battleTasksMutex;

public:
    GameController(Battlefield &battlefield);
    GameController(LogManager &logManager, Battlefield &battlefield);
    void fillRandomNPCs(Battlefield &battlefield);
    void startGame(BattleVisitor &battleVisitor);

private:
    void updateGame(BattleVisitor &battleVisitor);

    void displayMapPeriodically(std::atomic<bool> &isRunning);
    void moveNPCsPeriodically(std::atomic<bool> &isRunning);
    void detectBattles();

    void attackNPCs(BattleVisitor &battleVisitor);
    void moveNPCs(Battlefield *battlefield);

    void checkDeadNPCs();
    bool isBattleEnd(BattleVisitor &battleVisitor);
    void endGame();
};
