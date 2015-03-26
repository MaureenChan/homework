#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cstddef>
using std::size_t;

string::size_type find_char(const string &s, char c, string::size_type &occures) {
    auto ret = s.size();

    occures = 0;

    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i;
            ++occures;
        }
    }
    return ret;
}

vector<int>::const_iterator find_val( 
        vector<int>::const_iterator beg,
        vector<int>::const_iterator end,
        int value,
        vector<int>::size_type &occures) {
    auto res_iter = end;
    occures = 0;

    for ( ; beg != end; ++beg) 
        if (*beg == value) {
            if (res_iter == end)
                res_iter = beg;
            ++occures;
        }

    return res_iter;
}

int main() {
    string s;
    getline(cin, s);
    size_t ctr = 0;
    auto index = find_char(s, 'o', ctr);
    cout << index << " " << ctr << endl;

    vector<int> ivec;
    int i;

    while (cin >> i) 
        ivec.push_back(i);
    for (auto i : {42, 33, 92}) {
        auto it = find_val(ivec.begin(), ivec.end(), i, ctr);
        if (it == ivec.end())
            cout << i << " is not in the input data" << endl;
        else
            cout << i << " was at position "
                 << it - ivec.begin() << endl;
    }

    return 0;
}
