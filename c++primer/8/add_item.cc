#include "Sales_data.h"

#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main() {
    Sales_data data1, data2;
    read(cin, data1);
    read(cin, data2);


    if (data1.isbn() == data2.isbn()) {
        Sales_data sum = add(data1, data2);
        print(cout, sum);
        cout << endl;
    }

    return 0;
}

