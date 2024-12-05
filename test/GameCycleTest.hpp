#include <gtest/gtest.h>
#include "GameController.hpp"
#include "NPCFactory.hpp"
#include "Battlefield/Battlefield.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"

TEST(GameCycleTest, OrcAlive)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    GameController gameController(battlefield);
    BattleVisitor battleVisitor;

    std::shared_ptr<NPC> orc = npcFactory.createNPC(NPCType::Orc, 7, 0);
    std::shared_ptr<NPC> squirrel = npcFactory.createNPC(NPCType::Squirrel, 1, 0);
    std::shared_ptr<NPC> druid = npcFactory.createNPC(NPCType::Druid, 3, 9);
    battlefield.placeNPC(orc, 7, 0);
    battlefield.placeNPC(squirrel, 1, 0);
    battlefield.placeNPC(druid, 3, 9);

    gameController.startGame(battleVisitor);

    ASSERT_TRUE(battlefield.getNPC(1, 0) == nullptr);
    ASSERT_TRUE(battlefield.getNPC(3, 9) == nullptr);
}

TEST(GameCycleTest, EveryoneDead)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    GameController gameController(battlefield);
    BattleVisitor battleVisitor;

    std::shared_ptr<NPC> orc1 = npcFactory.createNPC(NPCType::Orc, 5, 0);
    std::shared_ptr<NPC> squirrel = npcFactory.createNPC(NPCType::Squirrel, 5, 1);
    std::shared_ptr<NPC> orc2 = npcFactory.createNPC(NPCType::Orc, 5, 2);
    battlefield.placeNPC(orc1, 5, 0);
    battlefield.placeNPC(squirrel, 5, 1);
    battlefield.placeNPC(orc2, 5, 2);

    gameController.startGame(battleVisitor);

    ASSERT_TRUE(battlefield.getNPC(5, 0) == nullptr);
    ASSERT_TRUE(battlefield.getNPC(5, 1) == nullptr);
    ASSERT_TRUE(battlefield.getNPC(5, 2) == nullptr);
}

TEST(GameCycleTest, EveryoneAlive)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    GameController gameController(battlefield);
    BattleVisitor battleVisitor;

    std::shared_ptr<NPC> orc = npcFactory.createNPC(NPCType::Orc, 0, 0);
    std::shared_ptr<NPC> squirrel = npcFactory.createNPC(NPCType::Squirrel, 5, 49);
    std::shared_ptr<NPC> druid = npcFactory.createNPC(NPCType::Druid, 49, 3);
    battlefield.placeNPC(orc, 0, 0);
    battlefield.placeNPC(squirrel, 5, 49);
    battlefield.placeNPC(druid, 49, 3);

    gameController.startGame(battleVisitor);

    ASSERT_TRUE(std::strcmp(battlefield.getNPC(0, 0)->getType(), "Orc") == 0);
    ASSERT_TRUE(std::strcmp(battlefield.getNPC(5, 49)->getType(), "Squirrel") == 0);
    ASSERT_TRUE(std::strcmp(battlefield.getNPC(49, 3)->getType(), "Druid") == 0);
}