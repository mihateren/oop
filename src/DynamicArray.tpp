#include "../include/DynamicArray.hpp"

template <typename T>
DynamicArray<T>::DynamicArray(std::pmr::memory_resource *resource, size_t capacity)
    : allocator_(resource), size_(0), capacity_(capacity)
{
    if (capacity <= 0)
    {
        throw std::invalid_argument("Capacity must be greater than 0");
    }

    data_ = allocator_.allocate(capacity);
    if (!data_)
    {
        throw std::bad_alloc();
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    clear();
    allocator_.deallocate(data_, capacity_);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() { return data_; }

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() { return data_ + size_; }

template <typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cbegin() const { return data_; }

template <typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cend() const { return data_ + size_; }

template <typename T>
bool DynamicArray<T>::empty() const { return size_ == 0; }

template <typename T>
size_t DynamicArray<T>::size() const { return size_; }

template <typename T>
size_t DynamicArray<T>::capacity() const { return capacity_; }

template <typename T>
const T &DynamicArray<T>::operator[](size_t i) const
{
    if (i >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

template <typename T>
T &DynamicArray<T>::operator[](size_t i)
{
    if (i >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

template <typename T>
void DynamicArray<T>::swap(DynamicArray<T> &other) noexcept
{
    if (this != &other)
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
}

template <typename T>
void DynamicArray<T>::clear()
{
    if (data_)
    {
        for (size_t i = 0; i < size_; ++i)
        {
            std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(allocator_, &data_[i]);
        }
        size_ = 0;
    }
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::erase(Iterator i)
{
    if (i == end())
    {
        return end();
    }

    size_t index = i - begin();
    for (size_t j = index; j < size_ - 1; ++j)
    {
        data_[j] = std::move(data_[j + 1]);
    }

    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(allocator_, &data_[size_ - 1]);
    --size_;

    return Iterator(&data_[index]);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::erase(Iterator start, Iterator end)
{
    if (start == end)
    {
        return end;
    }

    size_t startIdx = start - begin();
    size_t endIdx = end - begin();

    for (size_t i = endIdx; i < size_; ++i)
    {
        data_[startIdx + (i - endIdx)] = std::move(data_[i]);
    }

    for (size_t i = size_ - (endIdx - startIdx); i < size_; ++i)
    {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(allocator_, &data_[i]);
    }

    size_ -= (endIdx - startIdx);

    return Iterator(&data_[startIdx]);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::insert(Iterator i, const T &value)
{
    if (size_ == capacity_)
    {
        reserve(capacity_ * 2);
    }

    size_t index = i - begin();

    for (size_t j = size_; j > index; --j)
    {
        data_[j] = std::move(data_[j - 1]);
    }

    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(allocator_, &data_[index], value);

    ++size_;
    return Iterator(&data_[index]);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::insert(Iterator i, const T &value, size_t count)
{
    size_t index = i - begin();

    if (size_ + count > capacity_)
    {
        reserve(std::max(capacity_ * 2, size_ + count));
    }

    for (size_t j = size_; j > index; --j)
    {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(
            allocator_, data_ + j + count - 1, std::move(data_[j - 1]));
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(
            allocator_, data_ + j - 1);
    }

    for (size_t j = 0; j < count; ++j)
    {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(
            allocator_, data_ + index + j, value);
    }

    size_ += count;
    return begin() + index;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::insert(Iterator i, Iterator start, Iterator end)
{
    size_t index = i - begin();
    size_t count = end - start;

    if (size_ + count > capacity_)
    {
        reserve(std::max(capacity_ * 2, size_ + count));
    }

    for (size_t j = size_; j > index; --j)
    {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(
            allocator_, data_ + j + count - 1, std::move(data_[j - 1]));
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(
            allocator_, data_ + j - 1);
    }

    for (size_t j = 0; j < count; ++j)
    {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(
            allocator_, data_ + index + j, *(start + j));
    }

    size_ += count;
    return begin() + index;
}

template <typename T>
void DynamicArray<T>::push_back(const T &value)
{
    if (size_ == capacity_)
    {
        size_t newCapacity = capacity_ * 2;
        reserve(newCapacity);
    }

    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(allocator_, &data_[size_], value);
    ++size_;
}

template <typename T>
void DynamicArray<T>::pop_back()
{
    if (size_ == 0)
    {
        throw std::out_of_range("Attempt to pop from an empty array");
    }

    std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(allocator_, &data_[size_ - 1]);
    --size_;
}

template <typename T>
void DynamicArray<T>::reserve(size_t newCapacity)
{
    T *newData = allocator_.allocate(newCapacity);

    if (!newData)
    {
        throw std::bad_alloc();
    }

    for (size_t i = 0; i < size_; ++i)
    {
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::construct(allocator_, &newData[i], std::move(data_[i]));
        std::allocator_traits<std::pmr::polymorphic_allocator<T>>::destroy(allocator_, &data_[i]);
    }

    allocator_.deallocate(data_, capacity_);
    data_ = newData;
    capacity_ = newCapacity;
}
