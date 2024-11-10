#pragma once

#include <memory_resource>
#include <stdexcept>
#include <algorithm>

template <typename T>
class DynamicArray
{
public:
    using Iterator = T *;
    using ConstIterator = const T *;

    explicit DynamicArray(
        std::pmr::memory_resource *resource = std::pmr::get_default_resource(),
        size_t capacity = 50);
    ~DynamicArray();

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    const T &operator[](size_t i) const;
    T &operator[](size_t i);

    void swap(DynamicArray<T> &other) noexcept;
    void clear();

    Iterator erase(Iterator i);
    Iterator erase(Iterator start, Iterator end);

    Iterator insert(Iterator i, const T &value);
    Iterator insert(Iterator i, const T &value, size_t count);
    Iterator insert(Iterator i, Iterator start, Iterator end);
    void push_back(const T &value);
    void pop_back();

private:
    void reserve(size_t newCapacity);

    std::pmr::polymorphic_allocator<T> allocator_;
    T *data_;
    size_t size_;
    size_t capacity_;
};

#include "../src/DynamicArray.tpp"
