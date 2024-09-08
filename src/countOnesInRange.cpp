#include "../include/countOnesInRange.h"

int countOnesInRange(int lhv, int rhv) {
    int res = {0};
    for (int i = lhv; i <= rhv; i++) {
        int num = i;
        while (num > 0) {
            res += num % 2;
            num /= 2;
        }
    }
    return res;
}