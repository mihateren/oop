#pragma once
#include <initializer_list>
#include <string>

void validateDigit(unsigned char digit);

class Six {
public:
  Six();
  Six(const size_t& lengthOfNumber, unsigned char defaultValue = 0);
  Six(const std::initializer_list<unsigned char>& defaultValuesList);
  Six(const std::string& defaultValueString);
  Six(const Six& other);
  Six(Six&& other) noexcept;
  Six& operator=(const Six& other);
  Six& operator+=(const Six& other);
  Six& operator-=(const Six& other);
  Six& operator*=(const Six& other);
  bool operator==(const Six& other) const;
  bool operator<(const Six& other) const;
  bool operator>(const Six& other) const;
  size_t getSize() const;
  unsigned char* getData() const;
  virtual ~Six() noexcept;
private:
  unsigned char* data;
  size_t size; 
};

class InvalidDigitException : public std::invalid_argument {
public: 
    InvalidDigitException() :
        std::invalid_argument("Invalid digit: value must be between 0 and 5") {}
};

class SelfAssignmentException : public std::logic_error {
public: 
    SelfAssignmentException() :
        std::logic_error("Self-assignment error: cannot copy self") {}
};

class SizeMismatchException : public std::logic_error {
public:
    SizeMismatchException() :
        std::logic_error("Size mismatch error: the size of the first Six is smaller than the size of the second") {}
};

class SubtractionUnderflowException : public std::logic_error {
public:
    SubtractionUnderflowException() :
        std::logic_error("Subtraction underflow: the result of the subtraction is negative") {}
};


class MemoryAllocationException : public std::runtime_error {
public:
    MemoryAllocationException() :
        std::runtime_error("Memory allocation failed") {}
};