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

    ASSERT_TRUE(std::strcmp(orc->getType(), "Орк") == 0);
    ASSERT_TRUE(std::strcmp(squirrel->getType(), "Белка") == 0);
    ASSERT_TRUE(std::strcmp(druid->getType(), "Друид") == 0);
}

TEST(FactoryTest, FactoryWithCoordsTest)
{
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPCType::Orc, 100, 101);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPCType::Squirrel, 100, 102);
    std::shared_ptr<NPC> druid = factory.createNPC(NPCType::Druid, 100, 103);

    ASSERT_TRUE(std::strcmp(orc->getType(), "Орк") == 0);
    ASSERT_TRUE(std::strcmp(squirrel->getType(), "Белка") == 0);
    ASSERT_TRUE(std::strcmp(druid->getType(), "Друид") == 0);

    ASSERT_TRUE(orc->getPosition().x == 100);
    ASSERT_TRUE(orc->getPosition().y == 101);
    ASSERT_TRUE(squirrel->getPosition().x == 100);
    ASSERT_TRUE(squirrel->getPosition().y == 102);
    ASSERT_TRUE(druid->getPosition().x == 100);
    ASSERT_TRUE(druid->getPosition().y == 103);
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

    ASSERT_TRUE(std::strcmp(npcs[0]->getType(), "Орк") == 0);
    ASSERT_TRUE(std::strcmp(npcs[1]->getType(), "Белка") == 0);
    ASSERT_TRUE(std::strcmp(npcs[2]->getType(), "Друид") == 0);

    std::remove("testNPCs.txt");
}