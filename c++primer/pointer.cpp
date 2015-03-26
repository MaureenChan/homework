#include <iostream>
using namespace std;
int main() {
    int i = 42;
    int &r1 = i;
    const int &r2 = i;
    r1 = 0;
    cout << i
        << r1 
        << r2
        << endl;
}
