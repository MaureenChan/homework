#include <iostream>
using std::endl;
using std::cout;

#include <iterator>
using std::begin;
using std::end;

void print(const char *cp) {
    if (cp) 
        while (*cp) 
            cout << *cp++;
}

void print(const int *beg, const int *end) {
    while (beg != end) 
        cout << *beg++ << " ";

}

int main() {
    print("hi world!");
    cout << endl;

    int j[2] = {0, 1};
    print(begin(j), end(j));
    cout << endl;

    print(j, j + 2);
    cout << endl;

    return 0;
}
