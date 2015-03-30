#include "Version_test.h"

#include <string>
using std::string;

#ifdef STRING_NUMERIC_CONVS
using std::to_string;
using std::stod;
#endif

#include <iostream>
using std::cout;
using std::endl;

int main() {
    int i = 42;
    string s = to_string(i);

    double d = stod(s);
    cout << "i  = " << i << "s = " << s << " d is: " << d << endl;

    string s2 = "pi = 3.14";
    d = stod(s2.substr(s2.find_first_of("+-.0123456789")));

    cout << "d = " << d << " s = " << s << " s2 is: " << s2 << endl;
    return 0;
}
