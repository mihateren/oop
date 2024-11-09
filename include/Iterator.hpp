#pragma once

template <typename T>
class Iterator
{
public:
    explicit Iterator(T *ptr) : ptr_(ptr) {}

    T &operator*() const
    {
        return *ptr_;
    }

    T *operator->() const
    {
        return ptr_;
    }

    bool operator==(const Iterator &other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator &other) const
    {
        return ptr_ != other.ptr_;
    }

    Iterator &operator++()
    {
        ++ptr_;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    Iterator &operator--()
    {
        --ptr_;
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator temp = *this;
        --(*this);
        return temp;
    }

    Iterator operator+(size_t n) const
    {
        return Iterator(ptr_ + n);
    }

    Iterator operator-(size_t n) const
    {
        return Iterator(ptr_ - n);
    }

    Iterator &operator+=(size_t n)
    {
        ptr_ += n;
        return *this;
    }

    Iterator &operator-=(size_t n)
    {
        ptr_ -= n;
        return *this;
    }

    size_t operator-(const Iterator &other) const
    {
        return ptr_ - other.ptr_;
    }

private:
    T *ptr_;
};
