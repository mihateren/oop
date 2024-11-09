#include <gtest/gtest.h>
#include "../include/Iterator.hpp"
#include <iostream>
#include <vector>

TEST(testIterator, deferenceOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter(vect.data());

  ASSERT_TRUE(*iter == 1);
}

TEST(testIterator, arrowOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter(vect.data());

  ASSERT_TRUE(*iter.operator->() == 1);
}

TEST(testIterator, equalOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter1(vect.data());
  Iterator iter2(vect.data());

  ASSERT_TRUE(iter1 == iter2);
}

TEST(testIterator, notEqualOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter1(vect.data());
  Iterator iter2(vect.data() + vect.size());

  ASSERT_TRUE(iter1 != iter2);
}

TEST(testIterator, incrementOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter(vect.data());
  ++iter;

  ASSERT_TRUE(*iter == 2);
}

TEST(testIterator, postIncrementOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter(vect.data());
  Iterator oldIter = iter++;

  ASSERT_TRUE(*oldIter == 1);
  ASSERT_TRUE(*iter == 2);
}

TEST(testIterator, decrementOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter(vect.data() + vect.size() - 1);
  --iter;

  ASSERT_TRUE(*iter == 4);
}

TEST(testIterator, postDecrementOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator iter(vect.data() + vect.size() - 1);
  Iterator oldIter = iter--;
  
  ASSERT_TRUE(*oldIter == 5);
  ASSERT_TRUE(*iter == 4);
}

TEST(testIterator, additionOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator<int> iter(vect.data());
  Iterator<int> result = iter + 3;

  ASSERT_TRUE(*result == 4);
}

TEST(testIterator, subtractionOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator<int> iter(vect.data() + 4);
  Iterator<int> result = iter - 2;

  ASSERT_TRUE(*result == 3);
}

TEST(testIterator, plusEqualOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator<int> iter(vect.data());
  iter += 2; 

  ASSERT_TRUE(*iter == 3);
}

TEST(testIterator, minusEqualOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator<int> iter(vect.data() + 4); 
  iter -= 3;

  ASSERT_TRUE(*iter == 2);
}

TEST(testIterator, differenceOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  Iterator<int> iter1(vect.data());
  Iterator<int> iter2(vect.data() + 4);

  size_t diff = iter2 - iter1;

  ASSERT_TRUE(diff == 4);
}