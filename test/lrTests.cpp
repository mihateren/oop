#include <gtest/gtest.h>
#include "../include/Six.h"

TEST(SixTest, DefaultConstructor) {
    Six number;
    size_t expectedSize = 1;
    unsigned char expectedData[] = {'0'};

    size_t realSize = number.getSize();
    unsigned char* realData = number.getData();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realData[0] == expectedData[0]);
}

TEST(SixTest, ConstructorWithDefaultValue) {
    size_t length = 2;
    unsigned char defaultValue = '3';
    size_t expectedSize = 2;
    unsigned char expectedData[] = {'3', '3'};

    Six number(length, defaultValue);
    size_t realSize = number.getSize();
    unsigned char* realData = number.getData();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realData[0] == expectedData[0]);
    ASSERT_TRUE(realData[1] == expectedData[1]);
}

TEST(SixTest, ConstructorWithInitializerList) {
    std::initializer_list<unsigned char> digits = {'1', '2', '3'};
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Six number(digits);
    size_t realSize = number.getSize();
    unsigned char* realData = number.getData();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realData[0] == expectedData[0]);
    ASSERT_TRUE(realData[1] == expectedData[1]);
}

TEST(SixTest, ConstructorWithString) {
    std::string numberString = "123";
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Six number(numberString);
    size_t realSize = number.getSize();
    unsigned char* realData = number.getData();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realData[0] == expectedData[0]);
    ASSERT_TRUE(realData[1] == expectedData[1]);
    ASSERT_TRUE(realData[2] == expectedData[2]);
}

TEST(SixTest, CopyConstructor) {
    Six original({'1', '2', '3'});
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Six copy(original);
    size_t realSize = copy.getSize();
    unsigned char* realData = copy.getData();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realData[0] == expectedData[0]);
    ASSERT_TRUE(realData[1] == expectedData[1]);
    ASSERT_TRUE(realData[2] == expectedData[2]);
}

TEST(SixTest, MoveConstructor) {
    Six original({'1', '2', '3'});
    unsigned char expectedMovedData[] = {'1', '2', '3'};
    size_t expectedMovedSize = 3;
    unsigned char* expectedOriginalData = nullptr;
    size_t expectedOriginalSize = 0;
    
    Six moved(std::move(original));
    size_t movedSize = moved.getSize();
    unsigned char* movedData = moved.getData();

    ASSERT_TRUE(movedSize == expectedMovedSize);
    ASSERT_TRUE(movedData[0] == expectedMovedData[0]);
    ASSERT_TRUE(movedData[1] == expectedMovedData[1]);
    ASSERT_TRUE(movedData[2] == expectedMovedData[2]);
    ASSERT_TRUE(original.getSize() == expectedOriginalSize);
    ASSERT_TRUE(original.getData() == expectedOriginalData);
}


TEST(SixTest, AssignmentOperator) {
    Six original({'1', '2', '3'});
    Six assigned({'4', '5'});
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};
    
    assigned = original;
    unsigned char* realResult = assigned.getData();
    size_t realSize = assigned.getSize();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realResult[0] == expectedData[0]);
    ASSERT_TRUE(realResult[1] == expectedData[1]);
    ASSERT_TRUE(realResult[2] == expectedData[2]);
}


TEST(SixTest, AdditionOperator) {
    Six number1({'1', '2', '3'});
    Six number2({'2', '2', '2'});
    unsigned char expectedResult[] = {'3', '4', '5'};
    size_t expectedSize = 3;

    number1 += number2;
    unsigned char* realResult = number1.getData();
    size_t realSize = number1.getSize();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realResult[0] == expectedResult[0]);
    ASSERT_TRUE(realResult[1] == expectedResult[1]);
    ASSERT_TRUE(realResult[2] == expectedResult[2]);
}


TEST(SixTest, SubtractionOperator) {
    Six number1({'5', '4', '3'});
    Six number2({'2', '2', '2'});
    unsigned char expectedResult[] = {'3', '2', '1'};
    size_t expectedSize = 3;

    number1 -= number2;
    unsigned char* realResult = number1.getData();
    size_t realSize = number1.getSize();

    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realResult[0] == expectedResult[0]);
    ASSERT_TRUE(realResult[1] == expectedResult[1]);
    ASSERT_TRUE(realResult[2] == expectedResult[2]);
}


TEST(SixTest, MultiplicationOperator) {
    Six number1({'2', '1'});
    Six number2({'2', '2'});
    unsigned char expectedResult[] = {'4', '0', '3'};
    size_t expectedSize = 3;
    
    number1 *= number2;
    unsigned char* realResult = number1.getData();
    size_t realSize = number1.getSize();
    
    ASSERT_TRUE(realSize == expectedSize);
    ASSERT_TRUE(realResult[0] == expectedResult[0]);
    ASSERT_TRUE(realResult[1] == expectedResult[1]);
    ASSERT_TRUE(realResult[2] == expectedResult[2]);
}


TEST(SixTest, ComparisonOperators) {
    Six number1({'1', '2', '3'});
    Six number2({'1', '2', '3'});
    Six number3({'2', '2', '3'});

    bool is1Equal2 = (number1 == number2);
    bool is1LessThan2 = (number1 < number2);
    bool is1GreaterThan2 = (number1 > number2);
    bool is1LessThanNumber3 = (number1 < number3);
    bool is1GreaterThanNumber3 = (number1 > number3);

    ASSERT_TRUE(is1Equal2);
    ASSERT_FALSE(is1LessThan2);
    ASSERT_FALSE(is1GreaterThan2);
    ASSERT_TRUE(is1LessThanNumber3);
    ASSERT_FALSE(is1GreaterThanNumber3);
}


TEST(SixTest, InvalidDigitExceptionTest) {
    std::initializer_list<unsigned char> invalidDigits1 = { '6', '1' };
    std::initializer_list<unsigned char> invalidDigits2 = { 'a', '1' };

    EXPECT_THROW(Six number1(invalidDigits1), InvalidDigitException);
    EXPECT_THROW(Six number2(invalidDigits2), InvalidDigitException);
}

TEST(SixTest, SelfAssignmentExceptionTest) {
    Six number({'1', '2', '3'});

    EXPECT_THROW(number = number, SelfAssignmentException);
}

TEST(SixTest, SizeMismatchExceptionTest) {
    Six small({'1', '2'});
    Six large({'5', '5', '5'});

    EXPECT_THROW(small -= large, SizeMismatchException);
}

TEST(SixTest, SubtractionUnderflowExceptionTest) {
    Six number1({'1', '1', '1'});
    Six number2({'5', '5', '5'});

    EXPECT_THROW(number1 -= number2, SubtractionUnderflowException);
}

TEST(SixTest, MemoryAllocationExceptionTest) {
    size_t bigSize = SIZE_MAX;

    EXPECT_THROW(Six number(bigSize, '1'), MemoryAllocationException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
