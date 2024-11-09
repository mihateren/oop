#pragma once

#include <gtest/gtest.h>
#include "../include/DynamicArray.hpp"
#include "../include/Iterator.hpp"
#include "../include/ConstIterator.hpp"
#include "../include/FixedBlockMemoryResource.hpp"
#include <iostream>
#include <string>

struct MyStruct {
    int a;
    double b;
    std::string c;

    MyStruct(int _a, double _b, const std::string &_c) : a(_a), b(_b), c(_c) {}

    bool operator==(const MyStruct &other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(testDynamicArrayStruct, defaultConstructor)
{
    size_t expectedSize = 0;
    size_t expectedCapacity = 50;

    DynamicArray<MyStruct> array;
    size_t realSize = array.size();
    size_t realCapacity = array.capacity();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedCapacity == realCapacity);
}

TEST(testDynamicArrayStruct, beginOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    Iterator<MyStruct> it(array.begin());

    ASSERT_TRUE(*it == MyStruct(1, 1.1, "first"));
}

TEST(testDynamicArrayStruct, endOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    Iterator<MyStruct> it(array.end() - 1);

    ASSERT_TRUE(*it == MyStruct(3, 3.3, "third"));
}

TEST(testDynamicArrayStruct, cbeginOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    ConstIterator<MyStruct> it(array.cbegin());

    ASSERT_TRUE(*it == MyStruct(1, 1.1, "first"));
}

TEST(testDynamicArrayStruct, cendOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    ConstIterator<MyStruct> it(array.cend() - 1);

    ASSERT_TRUE(*it == MyStruct(3, 3.3, "third"));
}

TEST(testDynamicArrayStruct, emptyOperator)
{
    DynamicArray<MyStruct> array;

    ASSERT_TRUE(array.empty());
}

TEST(testDynamicArrayStruct, sizeOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    ASSERT_TRUE(array.size() == 3);
}

TEST(testDynamicArrayStruct, capacityOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    ASSERT_TRUE(array.capacity() == 50);
}

TEST(testDynamicArrayStruct, squareOperatorRead)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    ASSERT_TRUE(array[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array[1] == MyStruct(2, 2.2, "second"));
    ASSERT_TRUE(array[2] == MyStruct(3, 3.3, "third"));
}

TEST(testDynamicArrayStruct, squareOperatorWrite)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    array[0] = MyStruct(10, 10.1, "tenth");
    array[1] = MyStruct(20, 20.2, "twentieth");
    array[2] = MyStruct(30, 30.3, "thirtieth");

    ASSERT_TRUE(array[0] == MyStruct(10, 10.1, "tenth"));
    ASSERT_TRUE(array[1] == MyStruct(20, 20.2, "twentieth"));
    ASSERT_TRUE(array[2] == MyStruct(30, 30.3, "thirtieth"));
}

TEST(testDynamicArrayStruct, swapOperator)
{
    DynamicArray<MyStruct> array1;
    array1.push_back(MyStruct(1, 1.1, "first"));
    array1.push_back(MyStruct(2, 2.2, "second"));
    array1.push_back(MyStruct(3, 3.3, "third"));
    DynamicArray<MyStruct> array2;
    array2.push_back(MyStruct(4, 4.4, "fourth"));
    array2.push_back(MyStruct(5, 5.5, "fifth"));
    array2.push_back(MyStruct(6, 6.6, "sixth"));

    array1.swap(array2);

    ASSERT_TRUE(array1[0] == MyStruct(4, 4.4, "fourth"));
    ASSERT_TRUE(array1[1] == MyStruct(5, 5.5, "fifth"));
    ASSERT_TRUE(array1[2] == MyStruct(6, 6.6, "sixth"));
    ASSERT_TRUE(array2[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array2[1] == MyStruct(2, 2.2, "second"));
    ASSERT_TRUE(array2[2] == MyStruct(3, 3.3, "third"));
}

TEST(testDynamicArrayStruct, clearOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    array.clear();

    ASSERT_TRUE(array.empty());
}

TEST(testDynamicArrayStruct, eraseOperatorIterator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));
    array.push_back(MyStruct(4, 4.4, "fourth"));

    array.erase(array.begin() + 1);

    ASSERT_TRUE(array[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array[1] == MyStruct(3, 3.3, "third"));
    ASSERT_TRUE(array[2] == MyStruct(4, 4.4, "fourth"));
}

TEST(testDynamicArrayStruct, eraseOperatorStartEnd)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));
    array.push_back(MyStruct(4, 4.4, "fourth"));

    array.erase(array.begin() + 1, array.begin() + 3);

    ASSERT_TRUE(array[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array[1] == MyStruct(4, 4.4, "fourth"));
}

TEST(testDynamicArrayStruct, insertOperatorValue)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    array.insert(array.begin() + 1, MyStruct(4, 4.4, "fourth"));

    ASSERT_TRUE(array[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array[1] == MyStruct(4, 4.4, "fourth"));
    ASSERT_TRUE(array[2] == MyStruct(2, 2.2, "second"));
    ASSERT_TRUE(array[3] == MyStruct(3, 3.3, "third"));
}


TEST(testDynamicArrayStruct, pushBackOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    ASSERT_TRUE(array[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array[1] == MyStruct(2, 2.2, "second"));
    ASSERT_TRUE(array[2] == MyStruct(3, 3.3, "third"));
}

TEST(testDynamicArrayStruct, popBackOperator)
{
    DynamicArray<MyStruct> array;
    array.push_back(MyStruct(1, 1.1, "first"));
    array.push_back(MyStruct(2, 2.2, "second"));
    array.push_back(MyStruct(3, 3.3, "third"));

    array.pop_back();

    ASSERT_TRUE(array[0] == MyStruct(1, 1.1, "first"));
    ASSERT_TRUE(array[1] == MyStruct(2, 2.2, "second"));
    ASSERT_EQ(array.size(), 2);
}


