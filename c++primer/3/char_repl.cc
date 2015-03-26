#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

int main() {
    string str("some string"), orig = str;

    // first char
    if (!str.empty())
        cout << str[0] << endl;

    // first char to upper
    if (!str.empty())
        str[0] = toupper(str[0]);
    cout << str << endl;

    str = orig;

    // Another method to change first char to upper
    if (str.begin() != str.end()) {
        auto it = str.begin();
        *it = toupper(*it);
    }
    cout << "Anther Method:" << str << endl;

    str = orig;

    // print str x times before meet space
    for (decltype(str.size()) index = 0; 
         index != str.size() && !isspace(str[index]);
         ++index) 
        cout << index << " " << str << endl;
    str = orig;

    // Change to upper before space once
    for (auto it = str.begin(); it != str.end() && !isspace(*it); ++it)
        *it = toupper(*it);
    cout << str << endl;

    str = orig;

    // Change some upper twice
    decltype(str.size()) index = 0;
    while (index != str.size() && !isspace(str[index])) {
        str[index] = toupper(str[index]);
        ++index;
    }
    cout << str << endl;

    // Change some upper third times
    auto beg = str.begin();
    while (beg != str.end() && !isspace(*beg)) {
        *beg = toupper(*beg);
        ++beg;
    }

    cout << str << endl;

    str = orig;

    // print each char once;
    for (auto c : str) 
        cout << c << endl;

    // print a line full of *
    for (auto &c : str) 
        c = '*';
    cout << str << endl;

    str = orig;

    // iterator a string 
    for (decltype(str.size()) ix = 0; ix != str.size(); ++ix)
        cout << str[ix] << endl;

    // iterator a line make of *
    for (decltype(str.size()) ix = 0; ix != str.size(); ++ix)
        str[ix] = '*';
    cout << str << endl;

    str = orig;

    // iterator value 
    for (auto beg = str.begin(); beg != str.end(); ++beg) 
        cout << *beg << endl;

    for (auto beg = str.begin(); beg != str.end(); ++beg)
        *beg = '*';
    cout << str << endl;
    return 0;
}


