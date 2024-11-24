#include <gtest/gtest.h>
#include "GameController.hpp"
#include "NPCFactory.hpp"
#include "Battlefield/Battlefield.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"

TEST(GameCycleTest, DruidAlive)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    GameController gameController(battlefield);
    BattleVisitor battleVisitor;

    std::shared_ptr<NPC> orc = npcFactory.createNPC(NPCType::Orc, 7, 0);
    std::shared_ptr<NPC> squirrel = npcFactory.createNPC(NPCType::Squirrel, 1, 0);
    std::shared_ptr<NPC> druid = npcFactory.createNPC(NPCType::Druid, 3, 9);
    battlefield.placeNPC(orc);
    battlefield.placeNPC(squirrel);
    battlefield.placeNPC(druid);

    gameController.startGame(battleVisitor);

    ASSERT_TRUE(battlefield.getNPC(1, 0) == nullptr);
    ASSERT_TRUE(battlefield.getNPC(7, 0) == nullptr);
}

TEST(GameCycleTest, EveryoneDead)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    GameController gameController(battlefield);
    BattleVisitor battleVisitor;

    std::shared_ptr<NPC> orc1 = npcFactory.createNPC(NPCType::Orc, 100, 0);
    std::shared_ptr<NPC> squirrel = npcFactory.createNPC(NPCType::Squirrel, 100, 1);
    std::shared_ptr<NPC> orc2 = npcFactory.createNPC(NPCType::Orc, 100, 2);
    battlefield.placeNPC(orc1);
    battlefield.placeNPC(squirrel);
    battlefield.placeNPC(orc2);

    gameController.startGame(battleVisitor);

    ASSERT_TRUE(battlefield.getNPC(100, 0) == nullptr);
    ASSERT_TRUE(battlefield.getNPC(100, 1) == nullptr);
    ASSERT_TRUE(battlefield.getNPC(100, 2) == nullptr);
}

TEST(GameCycleTest, EveryoneAlive)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    GameController gameController(battlefield);
    BattleVisitor battleVisitor;

    std::shared_ptr<NPC> orc = npcFactory.createNPC(NPCType::Orc, 100, 0);
    std::shared_ptr<NPC> squirrel = npcFactory.createNPC(NPCType::Squirrel, 100, 200);
    std::shared_ptr<NPC> druid = npcFactory.createNPC(NPCType::Druid, 100, 300);
    battlefield.placeNPC(orc);
    battlefield.placeNPC(squirrel);
    battlefield.placeNPC(druid);

    gameController.startGame(battleVisitor);

    ASSERT_TRUE(std::strcmp(battlefield.getNPC(100, 0)->getType(), "Орк") == 0);
    ASSERT_TRUE(std::strcmp(battlefield.getNPC(100, 200)->getType(), "Белка") == 0);
    ASSERT_TRUE(std::strcmp(battlefield.getNPC(100, 300)->getType(), "Друид") == 0);
}