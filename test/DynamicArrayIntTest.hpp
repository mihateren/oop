#pragma once

#include <gtest/gtest.h>
#include "../include/DynamicArray.hpp"
#include "../include/Iterator.hpp"
#include "../include/ConstIterator.hpp"
#include "../include/FixedBlockMemoryResource.hpp"
#include <iostream>

TEST(testDynamicArrayInt, defaultConstructor)
{
    size_t expectedSize = 0;
    size_t expectedCapacity = 50;

    DynamicArray<int> array;
    size_t realSize = array.size();
    size_t realCapacity = array.capacity();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedCapacity == realCapacity);
}

TEST(testDynamicArrayInt, beginOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    Iterator<int> it(array.begin());

    ASSERT_TRUE(*it == 1);
}

TEST(testDynamicArrayInt, endOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    Iterator<int> it(array.end() - 1);

    ASSERT_TRUE(*it == 3);
}

TEST(testDynamicArrayInt, cbeginOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    ConstIterator<int> it(array.cbegin());

    ASSERT_TRUE(*it == 1);
}

TEST(testDynamicArrayInt, cendOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    ConstIterator<int> it(array.cend() - 1);

    ASSERT_TRUE(*it == 3);
}

TEST(testDynamicArrayInt, emptyOperator)
{
    DynamicArray<int> array;

    ASSERT_TRUE(array.empty());
}

TEST(testDynamicArrayInt, sizeOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    ASSERT_TRUE(array.size() == 3);
}

TEST(testDynamicArrayInt, capacityOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    ASSERT_TRUE(array.capacity() == 50);
}

TEST(testDynamicArrayInt, squareOperatorRead)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    ASSERT_TRUE(array[0] == 1);
    ASSERT_TRUE(array[1] == 2);
    ASSERT_TRUE(array[2] == 3);
}

TEST(testDynamicArrayInt, squareOperatorWrite)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array[0] = 10;
    array[1] = 20;
    array[2] = 30;

    ASSERT_TRUE(array[0] == 10);
    ASSERT_TRUE(array[1] == 20);
    ASSERT_TRUE(array[2] == 30);
}

TEST(testDynamicArrayInt, swapOperator)
{
    DynamicArray<int> array1;
    array1.push_back(1);
    array1.push_back(2);
    array1.push_back(3);
    DynamicArray<int> array2;
    array2.push_back(4);
    array2.push_back(5);
    array2.push_back(6);

    array1.swap(array2);

    ASSERT_TRUE(array1[0] == 4);
    ASSERT_TRUE(array1[1] == 5);
    ASSERT_TRUE(array1[2] == 6);
    ASSERT_TRUE(array2[0] == 1);
    ASSERT_TRUE(array2[1] == 2);
    ASSERT_TRUE(array2[2] == 3);
}

TEST(testDynamicArrayInt, clearOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.clear();

    ASSERT_TRUE(array.empty());
}

TEST(testDynamicArrayInt, eraseOperatorIterator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);

    array.erase(array.begin() + 1);

    ASSERT_TRUE(array[0] == 1);
    ASSERT_TRUE(array[1] == 3);
    ASSERT_TRUE(array[2] == 4);
}

TEST(testDynamicArrayInt, eraseOperatorStartEnd)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);

    array.erase(array.begin() + 1, array.begin() + 3);

    ASSERT_TRUE(array[0] == 1);
    ASSERT_TRUE(array[1] == 4);
}

TEST(testDynamicArrayInt, insertOperatorValue)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.insert(array.begin() + 1, 4);

    ASSERT_TRUE(array[0] == 1);
    ASSERT_TRUE(array[1] == 4);
    ASSERT_TRUE(array[2] == 2);
    ASSERT_TRUE(array[3] == 3);
}


TEST(testDynamicArrayInt, pushBackOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    ASSERT_TRUE(array[0] == 1);
    ASSERT_TRUE(array[1] == 2);
    ASSERT_TRUE(array[2] == 3);
}

TEST(testDynamicArrayInt, popBackOperator)
{
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.pop_back();

    ASSERT_TRUE(array[0] == 1);
    ASSERT_TRUE(array[1] == 2);
}
