#include <iostream>
#include "include/countOnesInRange.h"

int main() {
    int lhv, rhv;
    std::cout << "enter the left hand value: ";
    std::cin  >> lhv;
    std::cout << "enter the right hand value: ";
    std::cin  >> rhv;

    std::cout << "result: " << countOnesInRange(lhv, rhv) << std::endl;
    return 0;
}