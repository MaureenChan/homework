#include <iterator>
using std::begin;
using std::end;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

void print(const int ia[], size_t size) {
    for (size_t i = 0; i != size; ++i) {
        cout << ia[i] << endl;
    }
}

int main() {
    int j[] = {0,1};
    print(j, end(j) - begin(j));
    return 0;
}

