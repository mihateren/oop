#include <gtest/gtest.h>
#include "NPCTest.hpp"
#include "FactoryTest.hpp"
#include "BattleTest.hpp"
#include "BattlefieldTest.hpp"
#include "GameCycleTest.hpp"

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}