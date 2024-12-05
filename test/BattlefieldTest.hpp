#include <gtest/gtest.h>
#include "Battlefield/Battlefield.hpp"
#include "NPCFactory.hpp"

TEST(BattlefieldTest, PlaceNPC)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    std::shared_ptr<NPC> npc = npcFactory.createNPC(NPCType::Orc, 10, 20);
    int expectedX = 10;
    int expectedY = 20;

    battlefield.placeNPC(npc, 10, 20);
    int realX = npc->getPosition().x;
    int realY = npc->getPosition().y;

    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}

TEST(BattlefieldTest, RemoveNPC)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    std::shared_ptr<NPC> npc = npcFactory.createNPC(NPCType::Orc, 10, 20);

    battlefield.placeNPC(npc, 10, 20);
    battlefield.removeNPC(10, 20);
    std::shared_ptr<NPC> removedNPC = battlefield.getNPC(10, 20);

    ASSERT_TRUE(!removedNPC);
}

TEST(BattlefieldTest, GetNPC)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    std::shared_ptr<NPC> npc = npcFactory.createNPC(NPCType::Orc, 10, 20);

    battlefield.placeNPC(npc, 10, 20);
    std::shared_ptr<NPC> realNPC = battlefield.getNPC(10, 20);

    ASSERT_TRUE(npc == realNPC);
}

TEST(BattlefieldTest, FindTargetsSingleNPC)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    std::shared_ptr<NPC> npc = npcFactory.createNPC(NPCType::Orc, 10, 20);

    battlefield.placeNPC(npc, 10, 20);
    std::vector<std::shared_ptr<NPC>> targets;
    BattleVisitor battleVisitor;
    battlefield.findTargets(npc, targets);

    ASSERT_TRUE(targets.size() == 0);
}

TEST(BattlefieldTest, FindTargetsMultipleNPCs)
{
    NPCFactory npcFactory;
    Battlefield battlefield;
    std::shared_ptr<NPC> npc1 = npcFactory.createNPC(NPCType::Orc, 10, 20);
    std::shared_ptr<NPC> npc2 = npcFactory.createNPC(NPCType::Orc, 10, 21);
    std::shared_ptr<NPC> npc3 = npcFactory.createNPC(NPCType::Orc, 10, 22);

    battlefield.placeNPC(npc1, 10, 20);
    battlefield.placeNPC(npc2, 10, 21);
    battlefield.placeNPC(npc3, 10, 22);
    std::vector<std::shared_ptr<NPC>> targets;
    BattleVisitor battleVisitor;
    battlefield.findTargets(npc1, targets);

    ASSERT_TRUE(targets.size() == 2);
}