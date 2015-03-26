#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

void reset(int &i) {
    i = 0;
}

void reset(int *ip) {
    *ip = 0;
    ip = 0;
}

int main() {
    int j = 42;
    reset(j);
    cout << "j = " << j << endl;
    
    j = 42;
    reset(&j);
    cout << "j = " << j << endl;

    j = 42;
    int *p = &j;
    reset(p);
    cout << "j = " << *p << endl;
    return 0;
}
