#include <iostream>
#include <string>
#include <cstddef>
using namespace std;


int main() {
    const string hexdigits = "0123456789ABCDEF";

    cout << "Enter a series of numbers"
         << endl;

    string result;
    string::size_type n;
    while (cin >> n)
        if (n < hexdigits.size())
            result += hexdigits[n];

    cout << "Your number is:" << result << endl;
    return 0;
}
