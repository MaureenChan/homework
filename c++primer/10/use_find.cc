#include "head.h"

int main() {
    int ia[] = {27, 210, 12, 47, 109, 83};
    int val = 83;
    int *result = find(begin(ia), end(ia), val);
    cout << "The value " << val
         << (result == end(ia) ? " is not present" : " is present") << endl;

    result = find(ia + 1, ia + 4, val);

    cout << "The value " << val
         << (result == end(ia) ? " is not present" : " is present") << endl;
    vector<int> vec = {27, 210, 12, 47, 109, 83};

    val = 42;

    auto result2 = find(vec.cbegin(), vec.cend(), val);

    cout << "The value " << val 
         << (result2 == vec.cend() ? " is not present" : " is present") << endl;

    list<string> lst = {"val1", "val2", "val3"};

    string sval = "a value";

    auto result3 = find(lst.cbegin(), lst.cend(), sval);

    cout << "The value " << sval
         << (result3 == lst.cend() ? "is not present" : " is present") << end;
    return 0;
}
