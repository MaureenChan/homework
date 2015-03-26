#include "LocalMath.h"
int gcd(int v1, int v2) {
    while (v2) {
        int temp = v2;
        v2 = v1 % v2;
        v1 = temp;
    }
    return v1;
}

int fact(int val) {
    int ret = 1;
    while (val > 1) 
        ret *= val--;
    return ret;
}

int factorial(int val) {
    if (val > 1) 
        return factorial(val - 1) * val;
    return 1;
}

