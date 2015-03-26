#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <initializer_list>
using std::initializer_list;

#include <sstream>
using std::ostringstream;

struct ErrCode {
    ErrCode(int i) : num(i) {}
    string msg() {
        ostringstream s;
        s << "ErrCode " << num;
        return s.str();
    }

    int num;
};

void error_msg(ErrCode e, initializer_list<string> il) {
    cout << e.msg() << ": ";
    for (const auto &elem : il)
        cout << elem << " ";
    cout << endl;
}

void error_msg(initializer_list<string> il) {
    for (auto beg = il.begin(); beg != il.end(); ++beg)
        cout << *beg << " ";
    cout << endl;
}

vector<string> functionX() {
    string expected = "description", actual = "some other case";

    if (expected.empty()) 
        return {};
    else if (expected == actual) 
        return {"functionX", "okey"};
    else
        return {"functionX", expected, actual};
}

int main() {
    string expected = "description", actual = "some other case";
    initializer_list<int> li = {0,1,2,3};

    if (expected != actual)
        error_msg({"functionX", expected, actual});
    else
        error_msg({"functionX", "okey"});

    if (expected != actual) 
        error_msg(ErrCode(42), {"functionX", expected, actual});
    else
        error_msg(ErrCode(0), {"functionX", "okey"});

    error_msg({});

    auto results = functionX();
    for (auto i : results)
        cout << i << " ";
    cout << endl;

    return 0;
}
