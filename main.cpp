#include <iostream>
#include "include/countOnesInRange.h"

int main() {
    int start, end;
    std::cout << "enter the beginning of the sequence: ";
    std::cin  >> start;
    std::cout << "enter the ending of the sequence: ";
    std::cin  >> end;

    int totalOnes = 0;
    
    try {
        totalOnes = countOnesInRange(start, end);
        std::cout << "result: " << totalOnes << std::endl;
    } catch (const NegativeValueException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const InvalidRangeException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}