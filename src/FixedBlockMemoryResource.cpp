#include "../include/FixedBlockMemoryResource.hpp"


FixedBlockMemoryResource::FixedBlockMemoryResource(size_t itemSize, size_t itemCount)
{
    if (itemSize == 0)
    {
        throw std::invalid_argument("block_size cannot be 0");
    }

    if (itemCount == 0)
    {
        throw std::invalid_argument("itemCount cannot be 0");
    }

    resource_ = new char[itemSize * itemCount];
    itemSize_ = itemSize;
    itemCount_ = itemCount;

    for (size_t i = 0; i < itemCount_; i++)
    {
        void *block = static_cast<void *>(resource_ + i * itemSize_);
        freedBlocks_.push_back(block);
    }
}

FixedBlockMemoryResource::~FixedBlockMemoryResource()
{
    delete[] reinterpret_cast<char *>(resource_);
}

void *FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment)
{
    if (bytes == 0)
    {
        throw std::invalid_argument("bytes cannot be 0");
    }

    if (bytes > itemSize_)
    {
        throw std::invalid_argument("bytes cannot be greater than itemSize");
    }

    if (alignment == 0 || (alignment & (alignment - 1)) != 0)
    {
        throw std::invalid_argument("alignment must be a power of 2");
    }

    if (freedBlocks_.empty())
    {
        throw std::bad_alloc();
    }

    void *block = freedBlocks_.front();
    freedBlocks_.pop_front();

    uintptr_t blockAddress = reinterpret_cast<uintptr_t>(block);
    uintptr_t alignedAddress = blockAddress;

    if (alignedAddress % alignment != 0)
    {
        alignedAddress += alignment - (alignedAddress % alignment);
    }

    if (alignedAddress + bytes > blockAddress + itemSize_)
    {
        freedBlocks_.push_back(block);
        throw std::bad_alloc();
    }

    void *alignedBlock = reinterpret_cast<void *>(alignedAddress);
    allocatedBlocks_.push_back(alignedBlock);

    return alignedBlock;
}

void FixedBlockMemoryResource::do_deallocate(void *ptr, size_t bytes, size_t alignment)
{
    if (bytes == 0)
    {
        throw std::invalid_argument("bytes cannot be 0");
    }

    if (bytes > itemSize_)
    {
        throw std::invalid_argument("bytes cannot be greater than itemSize");
    }

    bool blockFound = false;
    for (auto it = allocatedBlocks_.begin(); it != allocatedBlocks_.end(); ++it)
    {
        if (*it == ptr)
        {
            allocatedBlocks_.erase(it);
            freedBlocks_.push_back(ptr);
            blockFound = true;
            break;
        }
    }

    if (!blockFound)
    {
        throw std::logic_error("Attempting to deallocate a block that was not allocated.");
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    const FixedBlockMemoryResource *otherResource = dynamic_cast<const FixedBlockMemoryResource *>(&other);

    if (otherResource == nullptr)
    {
        return false;
    }

    return itemSize_ == otherResource->itemSize_ && itemCount_ == otherResource->itemCount_;
}
