#include <gtest/gtest.h>
#include "Mobs/Druid.hpp"
#include "Mobs/Orc.hpp"
#include "Mobs/Squirrel.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"

TEST(BattleTest, OrcVsSquirrel)
{
    Orc orc;
    Squirrel squirrel;
    BattleVisitor battleVisitor;
    int expectedSquirrelHP = 0;

    squirrel.accept(battleVisitor, orc);
    int realSquirrelHP = squirrel.getHP();

    ASSERT_TRUE(expectedSquirrelHP == realSquirrelHP);
}

TEST(BattleTest, OrcVsDruid)
{
    Orc orc;
    Druid druid;
    BattleVisitor battleVisitor;
    int expectedDruidHP = 40;

    druid.accept(battleVisitor, orc);
    int realDruidHP = druid.getHP();

    ASSERT_TRUE(expectedDruidHP == realDruidHP);
}

TEST(BattleTest, OrcVsOrc)
{
    Orc orc1;
    Orc orc2;
    BattleVisitor battleVisitor;
    int expectedOrc1HP = 60;

    orc1.accept(battleVisitor, orc2);
    int realOrc1HP = orc1.getHP();

    ASSERT_TRUE(expectedOrc1HP == realOrc1HP);
}

TEST(BattleTest, DruidVsSquirrel)
{
    Druid druid;
    Squirrel squirrel;
    BattleVisitor battleVisitor;
    int expectedSquirrelHP = 0;

    squirrel.accept(battleVisitor, druid);
    int realSquirrelHP = squirrel.getHP();

    ASSERT_TRUE(expectedSquirrelHP == realSquirrelHP);
}

TEST(BattleTest, DruidVsOrc)
{
    Druid druid;
    Orc orc;
    BattleVisitor battleVisitor;
    int expectedOrcHP = 70;

    orc.accept(battleVisitor, druid);
    int realOrcHP = orc.getHP();

    ASSERT_TRUE(expectedOrcHP == realOrcHP);
}

TEST(BattleTest, DruidVsDruid)
{
    Druid druid1;
    Druid druid2;
    BattleVisitor battleVisitor;
    int expectedDruid1HP = 50;

    druid1.accept(battleVisitor, druid2);
    int realDruid1HP = druid1.getHP();

    ASSERT_TRUE(expectedDruid1HP == realDruid1HP);
}

TEST(BattleTest, SquirrelVsSquirrel)
{
    Squirrel squirrel1;
    Squirrel squirrel2;
    BattleVisitor battleVisitor;
    int expectedSquirrel1HP = 10;

    squirrel1.accept(battleVisitor, squirrel2);
    int realSquirrel1HP = squirrel1.getHP();

    ASSERT_TRUE(expectedSquirrel1HP == realSquirrel1HP);
}

TEST(BattleTest, SquirrelVsOrc)
{
    Squirrel squirrel;
    Orc orc;
    BattleVisitor battleVisitor;
    int expectedOrcHP = 100;

    orc.accept(battleVisitor, squirrel);
    int realOrcHP = orc.getHP();

    ASSERT_TRUE(expectedOrcHP == realOrcHP);
}

TEST(BattleTest, SquirrelVsDruid)
{
    Squirrel squirrel;
    Druid druid;
    BattleVisitor battleVisitor;
    int expectedDruidHP = 80;

    druid.accept(battleVisitor, squirrel);
    int realDruidHP = druid.getHP();

    ASSERT_TRUE(expectedDruidHP == realDruidHP);
}