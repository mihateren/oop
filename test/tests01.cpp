#include <gtest/gtest.h>
#include "../include/countOnesInRange.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(countOnesInRange(2, 7) == 11);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(countOnesInRange(0, 1) == 1);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(countOnesInRange(10, 15) == 17);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(countOnesInRange(1, 1) == 1);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(countOnesInRange(0, 0) == 0);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}