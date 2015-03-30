#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include "Sales_data.h"

int main() {
    Sales_data data1, data2;
    if (read(cin, data1) && read(cin, data2)) {
        if (data1.isbn() == data2.isbn()) {
            data1.combine(data2);
            print(cout, data1);
            cout << endl;
        }
    } else 
        cerr << "Input failed|" << endl;
    return 0;
}
