#include <gtest/gtest.h>
#include "./IteratorTest.hpp"
#include "./ConstIteratorTest.hpp"
#include "./DynamicArrayIntTest.hpp"
#include "./DynamicArrayStructTest.hpp"
// #include "./MemoryResourceTest.hpp"

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}