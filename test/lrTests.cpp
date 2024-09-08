#include <gtest/gtest.h>
#include "../include/countOnesInRange.h"

TEST(CountOnesInRangeTest, ReturnsCorrectResultForRange2To7)
{
    int start = 2;
    int end = 7;
    int result = countOnesInRange(start, end);
    ASSERT_TRUE(result == 11);
}

TEST(CountOnesInRangeTest, ReturnsCorrectResultForRange0To1)
{
    int start = 0;
    int end = 1;
    int result = countOnesInRange(start, end);
    ASSERT_TRUE(result == 1);
}

TEST(CountOnesInRangeTest, ReturnsCorrectResultForRange0To0)
{
    int start = 0;
    int end = 0;
    int result = countOnesInRange(start, end);
    ASSERT_TRUE(result == 0);
}

TEST(CountOnesInRangeTest, ReturnsCorrectResultForRange1To1)
{
    int start = 1;
    int end = 1;
    int result = countOnesInRange(start, end);
    ASSERT_TRUE(result == 1);
}

TEST(CountOnesInRangeTest, ThrowsNegativeValueExceptionForNegativeStart)
{
    int start = -1;
    int end = 7;
    ASSERT_THROW(countOnesInRange(start, end), NegativeValueException);
}

TEST(CountOnesInRangeTest, ThrowsNegativeValueExceptionForNegativeStartAndEnd)
{
    int start = -1;
    int end = -10;
    ASSERT_THROW(countOnesInRange(start, end), NegativeValueException);
}

TEST(CountOnesInRangeTest, ThrowsInvalidRangeExceptionForEndingGreaterThanBeginning)
{
    int start = 5;
    int end = 1;
    ASSERT_THROW(countOnesInRange(start, end), InvalidRangeException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
