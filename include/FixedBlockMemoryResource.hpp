#pragma once

#include <memory_resource>
#include <list>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <new>

class FixedBlockMemoryResource : public std::pmr::memory_resource
{
public:
    FixedBlockMemoryResource(size_t itemSize, size_t itemCount);
    ~FixedBlockMemoryResource();

protected:
    void *do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override;

private:
    size_t itemSize_;
    size_t itemCount_;
    void *resource_;
    std::list<void *> allocatedBlocks_;
    std::list<void *> freedBlocks_;
};
