#include <gtest/gtest.h>
#include "../include/FixedBlockMemoryResource.hpp"

// Чтобы протестировать замените private и protected в FixedBlockMemoryResource на public

TEST(FixedBlockMemoryResource, ConstructorThrowsWhenItemSizeIsZero)
{
    EXPECT_THROW(FixedBlockMemoryResource(0, 10), std::invalid_argument);
}

TEST(FixedBlockMemoryResource, ConstructorAllocatesMemory)
{
    FixedBlockMemoryResource resource(8, 10);
    ASSERT_NO_THROW(FixedBlockMemoryResource(8, 10));
}

TEST(FixedBlockMemoryResource, AllocateThrowsWhenBytesExceedItemSize)
{
    FixedBlockMemoryResource resource(8, 10);
    EXPECT_THROW(resource.do_allocate(16, 8), std::invalid_argument);
}

TEST(FixedBlockMemoryResource, AllocateThrowsWhenAlignmentIsNotPowerOfTwo)
{
    FixedBlockMemoryResource resource(8, 10);
    EXPECT_THROW(resource.do_allocate(8, 3), std::invalid_argument);
}

TEST(FixedBlockMemoryResource, AllocateThrowsWhenAlignmentIsZero)
{
    FixedBlockMemoryResource resource(8, 10);
    EXPECT_THROW(resource.do_allocate(8, 0), std::invalid_argument);
}

TEST(FixedBlockMemoryResource, AllocateThrowsWhenNoFreedBlocks)
{
    FixedBlockMemoryResource resource(8, 1);
    void *block = resource.do_allocate(8, 8);
    EXPECT_THROW(resource.do_allocate(8, 8), std::bad_alloc);
}

TEST(FixedBlockMemoryResource, AllocateReturnsAlignedBlock)
{
    FixedBlockMemoryResource resource(8, 10);
    void *block = resource.do_allocate(8, 8);
    ASSERT_NE(block, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(block) % 8, 0);
}

TEST(FixedBlockMemoryResource, DeallocateThrowsWhenBlockNotAllocated)
{
    FixedBlockMemoryResource resource(8, 10);
    void *block = reinterpret_cast<void *>(0x12345678);
    EXPECT_THROW(resource.do_deallocate(block, 8, 8), std::logic_error);
}

TEST(FixedBlockMemoryResource, DeallocateWorksWhenBlockAllocated)
{
    FixedBlockMemoryResource resource(8, 10);
    void *block = resource.do_allocate(8, 8);
    ASSERT_NO_THROW(resource.do_deallocate(block, 8, 8));
}

TEST(FixedBlockMemoryResource, DeallocateAddsBlockBackToFreedList)
{
    FixedBlockMemoryResource resource(8, 10);
    void *block = resource.do_allocate(8, 8);
    size_t freedBlocksBefore = resource.freedBlocks_.size();
    resource.do_deallocate(block, 8, 8);
    size_t freedBlocksAfter = resource.freedBlocks_.size();
    EXPECT_EQ(freedBlocksAfter, freedBlocksBefore + 1);
}

TEST(FixedBlockMemoryResource, IsEqualReturnsTrueForSameInstance)
{
    FixedBlockMemoryResource resource1(8, 10);
    FixedBlockMemoryResource resource2(8, 10);
    EXPECT_TRUE(resource1.do_is_equal(resource2));
}

TEST(FixedBlockMemoryResource, IsEqualReturnsFalseForDifferentInstance)
{
    FixedBlockMemoryResource resource1(8, 10);
    FixedBlockMemoryResource resource2(16, 5);
    EXPECT_FALSE(resource1.do_is_equal(resource2));
}
