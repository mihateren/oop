#pragma once

#include <stdexcept>

class NegativeValueException : public std::invalid_argument {
public:
    NegativeValueException() : 
        std::invalid_argument("invalid input, beginning and ending must be greater than 0") {}
};

class InvalidRangeException : public std::out_of_range {
public:
    InvalidRangeException() : 
        std::out_of_range("invalid input, ending must be greater than beginning") {}
};

int countOnesInRange(int start, int end);
