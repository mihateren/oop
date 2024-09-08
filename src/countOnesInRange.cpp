#include "../include/countOnesInRange.h"

int countOnesInRange(int start, int end) {

    if (start < 0 || end < 0) {
        throw NegativeValueException();
    }

    if (end < start) {
        throw InvalidRangeException();
    }

    int totalOnes = {0};
    for (int i = start; i <= end; i++) {
        int num = i;
        while (num > 0) {
            totalOnes += num % 2;
            num /= 2;
        }
    }
    return totalOnes;
}