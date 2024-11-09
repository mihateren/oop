#include <gtest/gtest.h>
#include "../include/ConstIterator.hpp"
#include <vector>

TEST(testConstIterator, deferenceOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter(vect.data());

  ASSERT_TRUE(*constIter == 1);
}

TEST(testConstIterator, arrowOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter(vect.data());

  ASSERT_TRUE(*constIter.operator->() == 1);
}

TEST(testConstIterator, equalOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter1(vect.data());
  ConstIterator constIter2(vect.data());

  ASSERT_TRUE(constIter1 == constIter2);
}

TEST(testConstIterator, notEqualOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter1(vect.data());
  ConstIterator constIter2(vect.data() + vect.size());

  ASSERT_TRUE(constIter1 != constIter2);
}

TEST(testConstIterator, incrementOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter(vect.data());
  ++constIter;

  ASSERT_TRUE(*constIter == 2);
}

TEST(testConstIterator, postIncrementOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter(vect.data());
  ConstIterator oldIter = constIter++;

  ASSERT_TRUE(*oldIter == 1);
  ASSERT_TRUE(*constIter == 2);
}

TEST(testConstIterator, decrementOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter(vect.data() + vect.size() - 1);
  --constIter;
  
  ASSERT_TRUE(*constIter == 4);
}

TEST(testConstIterator, postDecrementOperator) {
  const std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator constIter(vect.data() + vect.size() - 1);
  ConstIterator oldIter = constIter--;

  ASSERT_TRUE(*oldIter == 5);
  ASSERT_TRUE(*constIter == 4);
}

TEST(testConstIterator, additionOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator<int> iter(vect.data());
  ConstIterator<int> result = iter + 3;

  ASSERT_TRUE(*result == 4);
}

TEST(testConstIterator, subtractionOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator<int> iter(vect.data() + 4);
  ConstIterator<int> result = iter - 2;

  ASSERT_TRUE(*result == 3);
}

TEST(testConstIterator, plusEqualOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator<int> iter(vect.data());
  iter += 2; 

  ASSERT_TRUE(*iter == 3);
}

TEST(testConstIterator, minusEqualOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator<int> iter(vect.data() + 4); 
  iter -= 3;

  ASSERT_TRUE(*iter == 2);
}

TEST(testConstIterator, differenceOperator) {
  std::vector<int> vect = {1, 2, 3, 4, 5};

  ConstIterator<int> iter1(vect.data());
  ConstIterator<int> iter2(vect.data() + 4);

  size_t diff = iter2 - iter1;

  ASSERT_TRUE(diff == 4);
}
