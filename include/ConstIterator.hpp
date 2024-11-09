#pragma once

template <typename T>
class ConstIterator
{
public:
  using IteratorType = const T;

  explicit ConstIterator(const IteratorType *ptr) : ptr_(ptr) {}

  const IteratorType &operator*() const
  {
    return *ptr_;
  }

  const IteratorType *operator->() const
  {
    return ptr_;
  }

  bool operator==(ConstIterator const &other) const
  {
    return ptr_ == other.ptr_;
  }

  bool operator!=(ConstIterator const &other) const
  {
    return ptr_ != other.ptr_;
  }

  ConstIterator &operator++()
  {
    ++ptr_;
    return *this;
  }

  ConstIterator operator++(int)
  {
    ConstIterator tmp = *this;
    ptr_++;
    return tmp;
  }

  ConstIterator &operator--()
  {
    --ptr_;
    return *this;
  }

  ConstIterator operator--(int)
  {
    ConstIterator tmp = *this;
    ptr_--;
    return tmp;
  }

  ConstIterator operator+(size_t n) const
  {
    return ConstIterator(ptr_ + n);
  }

  ConstIterator operator-(size_t n) const
  {
    return ConstIterator(ptr_ - n);
  }

  ConstIterator &operator+=(size_t n)
  {
    ptr_ += n;
    return *this;
  }

  ConstIterator &operator-=(size_t n)
  {
    ptr_ -= n;
    return *this;
  }

  size_t operator-(const ConstIterator &other) const
  {
    return ptr_ - other.ptr_;
  }

private:
  const IteratorType *ptr_;
};
