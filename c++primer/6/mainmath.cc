#include "LocalMath.h"
#include <iostream>
using std::cout; 
using std::endl;

int main() {
    int f = fact(5);
    cout << "5! is " << f << endl;

    int i = 5;
    int j = fact(i);
    cout << i << "! is " << j << endl;

    const int ci = 3;
    int k = fact(ci);
    cout << ci << "! is " << k << endl;
    return 0;
}
