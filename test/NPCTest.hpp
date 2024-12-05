#include <gtest/gtest.h>
#include "Mobs/Druid.hpp"
#include "Mobs/Orc.hpp"
#include "Mobs/Squirrel.hpp"

TEST(testNPC, druidConstructorWithoutParameters)
{
    Druid druid;

    int expectedHealth = 80;
    int expectedMoveDistance = 10;
    int expectedAttackDistance = 10;
    int expectedAttackPower = 30;
    int expectedX = 0;
    int expectedY = 0;

    int realHealth = druid.getHP();
    int realMoveDistance = druid.getMoveDistance();
    int realAttackDistance = druid.getAttackDistance();
    int realAttackPower = druid.getAttackPower();
    int realX = druid.getPosition().x;
    int realY = druid.getPosition().y;

    ASSERT_TRUE(expectedHealth == realHealth);
    ASSERT_TRUE(expectedAttackDistance == realAttackDistance);
    ASSERT_TRUE(expectedMoveDistance == realMoveDistance);
    ASSERT_TRUE(expectedAttackPower == realAttackPower);
    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}

TEST(testNPC, orcConstructorWithoutParameters)
{
    Orc orc;

    int expectedHealth = 100;
    int expectedMoveDistance = 20;
    int expectedAttackDistance = 10;
    int expectedAttackPower = 40;
    int expectedX = 0;
    int expectedY = 0;

    int realHealth = orc.getHP();
    int realMoveDistance = orc.getMoveDistance();
    int realAttackDistance = orc.getAttackDistance();
    int realAttackPower = orc.getAttackPower();
    int realX = orc.getPosition().x;
    int realY = orc.getPosition().y;

    ASSERT_TRUE(expectedHealth == realHealth);
    ASSERT_TRUE(expectedMoveDistance == realMoveDistance);
    ASSERT_TRUE(expectedAttackDistance == realAttackDistance);
    ASSERT_TRUE(expectedAttackPower == realAttackPower);
    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}

TEST(testNPC, squirrelConstructorWithoutParameters)
{
    Squirrel squirrel;

    int expectedHealth = 10;
    int expectedMoveDistance = 5;
    int expectedAttackDistance = 5;
    int expectedAttackPower = 0;
    int expectedX = 0;
    int expectedY = 0;

    int realHealth = squirrel.getHP();
    int realMoveDistance = squirrel.getMoveDistance();
    int realAttackDistance = squirrel.getAttackDistance();
    int realAttackPower = squirrel.getAttackPower();
    int realX = squirrel.getPosition().x;
    int realY = squirrel.getPosition().y;

    ASSERT_TRUE(expectedHealth == realHealth);
    ASSERT_TRUE(expectedMoveDistance == realMoveDistance);
    ASSERT_TRUE(expectedAttackDistance == realAttackDistance);
    ASSERT_TRUE(expectedAttackPower == realAttackPower);
    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}

TEST(testNPC, druidConstructorWithParameters)
{
    Druid druid(80, 10, 10, 30, 10, 10);

    int expectedHealth = 80;
    int expectedMoveDistance = 10;
    int expectedAttackDistance = 10;
    int expectedAttackPower = 30;
    int expectedX = 10;
    int expectedY = 10;

    int realHealth = druid.getHP();
    int realMoveDistance = druid.getMoveDistance();
    int realAttackDistance = druid.getAttackDistance();
    int realAttackPower = druid.getAttackPower();
    int realX = druid.getPosition().x;
    int realY = druid.getPosition().y;

    ASSERT_TRUE(expectedHealth == realHealth);
    ASSERT_TRUE(expectedMoveDistance == realMoveDistance);
    ASSERT_TRUE(expectedAttackDistance == realAttackDistance);
    ASSERT_TRUE(expectedAttackPower == realAttackPower);
    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}

TEST(testNPC, orcConstructorWithParameters)
{
    Orc orc(100, 20, 10, 40, 10, 10);

    int expectedHealth = 100;
    int expectedMoveDistance = 20;
    int expectedAttackDistance = 10;
    int expectedAttackPower = 40;
    int expectedX = 10;
    int expectedY = 10;

    int realHealth = orc.getHP();
    int realMoveDistance = orc.getMoveDistance();
    int realAttackDistance = orc.getAttackDistance();
    int realAttackPower = orc.getAttackPower();
    int realX = orc.getPosition().x;
    int realY = orc.getPosition().y;

    ASSERT_TRUE(expectedHealth == realHealth);
    ASSERT_TRUE(expectedMoveDistance == realMoveDistance);
    ASSERT_TRUE(expectedAttackDistance == realAttackDistance);
    ASSERT_TRUE(expectedAttackPower == realAttackPower);
    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}

TEST(testNPC, squirrelConstructorWithParameters)
{
    Squirrel squirrel(100, 5, 5, 10, 10, 10);

    int expectedHealth = 100;
    int expectedMoveDistance = 5;
    int expectedAttackDistance = 5;
    int expectedAttackPower = 10;
    int expectedX = 10;
    int expectedY = 10;

    int realHealth = squirrel.getHP();
    int realMoveDistance = squirrel.getMoveDistance();
    int realAttackDistance = squirrel.getAttackDistance();
    int realAttackPower = squirrel.getAttackPower();
    int realX = squirrel.getPosition().x;
    int realY = squirrel.getPosition().y;

    ASSERT_TRUE(expectedHealth == realHealth);
    ASSERT_TRUE(expectedMoveDistance == realMoveDistance);
    ASSERT_TRUE(expectedAttackDistance == realAttackDistance);
    ASSERT_TRUE(expectedAttackPower == realAttackPower);
    ASSERT_TRUE(expectedX == realX);
    ASSERT_TRUE(expectedY == realY);
}