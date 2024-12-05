#include <gtest/gtest.h>
#include "Mobs/Druid.hpp"
#include "Mobs/Orc.hpp"
#include "Mobs/Squirrel.hpp"
#include "NPCFactory.hpp"
#include <fstream>
#include <cstring>

TEST(FactoryTest, FactoryTest)
{
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPCType::Orc);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPCType::Squirrel);
    std::shared_ptr<NPC> druid = factory.createNPC(NPCType::Druid);

    ASSERT_TRUE(std::strcmp(orc->getType(), "Orc") == 0);
    ASSERT_TRUE(std::strcmp(squirrel->getType(), "Squirrel") == 0);
    ASSERT_TRUE(std::strcmp(druid->getType(), "Druid") == 0);
}

TEST(FactoryTest, FactoryWithCoordsTest)
{
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPCType::Orc, 0, 4);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPCType::Squirrel, 0, 5);
    std::shared_ptr<NPC> druid = factory.createNPC(NPCType::Druid, 0, 6);

    ASSERT_TRUE(std::strcmp(orc->getType(), "Orc") == 0);
    ASSERT_TRUE(std::strcmp(squirrel->getType(), "Squirrel") == 0);
    ASSERT_TRUE(std::strcmp(druid->getType(), "Druid") == 0);

    ASSERT_TRUE(orc->getPosition().x == 0);
    ASSERT_TRUE(orc->getPosition().y == 4);
    ASSERT_TRUE(squirrel->getPosition().x == 0);
    ASSERT_TRUE(squirrel->getPosition().y == 5);
    ASSERT_TRUE(druid->getPosition().x == 0);
    ASSERT_TRUE(druid->getPosition().y == 6);
}

TEST(FactoryTest, FactoryFromFileTest)
{
    {
        std::ofstream clearFile("testNPCs.txt", std::ios::out | std::ios::trunc);
        ASSERT_TRUE(clearFile.is_open());
    }

    std::ofstream testFile("testNPCs.txt", std::ios::out);
    ASSERT_TRUE(testFile.is_open());

    testFile << "Orc 0 1\n";
    testFile << "Squirrel 0 2\n";
    testFile << "Druid 0 3\n";
    testFile.close();

    NPCFactory factory;
    std::vector<std::shared_ptr<NPC>> npcs = factory.createNPCFromFile("testNPCs.txt");

    ASSERT_TRUE(std::strcmp(npcs[0]->getType(), "Orc") == 0);
    ASSERT_TRUE(std::strcmp(npcs[1]->getType(), "Squirrel") == 0);
    ASSERT_TRUE(std::strcmp(npcs[2]->getType(), "Druid") == 0);

    std::remove("testNPCs.txt");
}