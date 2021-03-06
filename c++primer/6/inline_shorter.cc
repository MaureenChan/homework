#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

inline const string &
shorterString(const string &s1, const string &s2) {
    return s1.size() <= s2.size() ? s1 : s2;
}

int main() {
    string s1("successes"), s2("failure");
    cout << shorterString(s1, s2) << endl;

    cout << shorterString(s1, s2).size() << endl;
    cout << (s1.size() < s2.size() ? s1 : s2) << endl;
    return 0;

}
