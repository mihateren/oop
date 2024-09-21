#include <iostream>
#include "./../include/Six.h"
#include <stdexcept>

void validateDigit(unsigned char digit) {
    if (digit < '0' || digit > '5') {
        throw InvalidDigitException();
    }
}

unsigned char* allocateMemory(size_t size) {
    unsigned char* ptr = new(std::nothrow) unsigned char[size]{0};
    if (!ptr) {
        throw MemoryAllocationException();
    }
    return ptr;
}

Six::Six() : size{1}, data{allocateMemory(1)} {
    data[0] = '0';
}

Six::Six(const size_t& lengthOfNumber, unsigned char defaultValue) {
    validateDigit(defaultValue);
    size = lengthOfNumber;
    data = allocateMemory(lengthOfNumber);

    for (size_t i = 0; i < lengthOfNumber; ++i) {
        data[i] = defaultValue;
    }
}


Six::Six(const std::initializer_list<unsigned char>& defaultValuesList) {
    size = defaultValuesList.size();
    data = allocateMemory(size);

    size_t i = 0;
    for (unsigned char digit : defaultValuesList) {
        validateDigit(digit);
        data[i++] = digit;
    }
}

Six::Six(const std::string& defaultValueString) {
    size = defaultValueString.size();
    data = allocateMemory(size);

    for (size_t i = 0; i < size; i++) {
        validateDigit(defaultValueString[i]);
        data[i] = defaultValueString[i];
    }
}

Six::Six(const Six& other) {
    if (this == &other) {
        throw SelfAssignmentException();
    }

    size = other.size;
    data = allocateMemory(size);

    unsigned char* otherData = other.getData();
    for (size_t i = 0; i < size; ++i) {
        data[i] = otherData[i];
    }
}


Six::Six(Six&& other) noexcept {
    size = other.size;
    data = other.data;
    other.data = nullptr;
    other.size = 0;
}

Six& Six::operator=(const Six& other) {
    if (this == &other) {
        throw SelfAssignmentException();
    }
    
    delete[] data;
    size = other.size;
    data = allocateMemory(size);
    
    unsigned char* otherData = other.getData(); 
    for (size_t i = 0; i < size; ++i) {
        data[i] = otherData[i];
    }
    
    return *this;
}


Six& Six::operator+=(const Six& other) {
    int carry = 0;
    size_t maxSize = std::max(size, other.size);
    unsigned char* newData = allocateMemory(maxSize + 1);
    
    for (size_t i = 0; i < maxSize; i++) {
        int sum = carry;
        if (i < size) {
            sum += data[i] - '0';
        }
        if (i < other.size) {
            sum += other.data[i] - '0';
        }
        newData[i] = (sum % 6) + '0';
        carry = sum / 6;
    }

    if (carry > 0) {
        newData[maxSize] = carry + '0';
        maxSize++;
    }

    delete[] data;
    data = newData;
    size = maxSize;

    return *this;
}

Six& Six::operator-=(const Six& other) {
    if (size < other.size) {
        throw SizeMismatchException();
    }

    int carry = 0;
    for (size_t i = 0; i < size; i++) {
        int otherDigit = (i < other.size) ? (other.data[i] - '0') : 0;
        int diff = (data[i] - '0') - otherDigit - carry;

        if (diff < 0) {
            data[i] = diff + 6 + '0';
            carry = 1;
        } else {
            data[i] = diff + '0';
            carry = 0;
        }
    }

    if (carry != 0) {
        throw SubtractionUnderflowException();
    }
    return *this;
}

Six& Six::operator*=(const Six& other) {
    size_t resultMaxSize = size + other.size + 1;
    unsigned char* resultData = allocateMemory(resultMaxSize);

    if (!resultData) {
        throw MemoryAllocationException();
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < other.size; j++) {
            int product = (data[i] - '0') * (other.data[j] - '0');
            resultData[i + j] += product;
        }
    }

    for (size_t k = 0; k < resultMaxSize; k++) {
        if (resultData[k] >= 6) {
            resultData[k + 1] += resultData[k] / 6;
            resultData[k] %= 6;
        }
    }

    size_t resultSize = resultMaxSize;
    do  {
        resultSize--;
    } while (resultSize > 1 && resultData[resultSize - 1] == 0);

    delete[] data;
    data = allocateMemory(resultSize);
    if (!data) {
        delete[] resultData;
        throw MemoryAllocationException();
    }

    for (size_t i = 0; i < resultSize; i++) {
        data[i] = resultData[i] + '0';
    }

    delete[] resultData;
    size = resultSize;

    return *this;
}



bool Six::operator==(const Six& other) const {
  if (size != other.size) {
    return false;
  }

  for (size_t i = 0; i < size; i++) {
    if (data[i] != other.data[i]) {
      return false;
    }
  }
  return true;
}

bool Six::operator<(const Six& other) const {
    if (size < other.size) {
        return true;
    }
    if (size > other.size) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (data[i] < other.data[i]) {
            return true;
        }
        if (data[i] > other.data[i]) {
            return false;
        }
    }
    return false;
}

bool Six::operator>(const Six& other) const {
    if (size > other.size) {
        return true;
    }
    if (size < other.size) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (data[i] > other.data[i]) {
            return true;
        }
        if (data[i] < other.data[i]) {
            return false;
        }
    }
    return false;
}


size_t Six::getSize() const {
  return size;
}

unsigned char* Six::getData() const {
  return data;
}

Six::~Six() noexcept {
  delete[] data;
  data = nullptr;
  size = 0;
}
