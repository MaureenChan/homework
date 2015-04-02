#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace std::placeholders;
ostream &print(ostream &os, const string &s, char c) {
    return os << s << c;
}

int main() {
    string s;
    vector<string> words;
    while (cin >> s) {
        words.push_back(s);
    }

    for_each(words.begin(), words.end(), 
             bind(print, ref(cout), _1, ' '));

    cout << endl;

    ofstream os("outFile1");
    for_each(words.begin(), words.end(), 
             bind(print, ref(os), _1, ' '));
    os << endl;

    ifstream is("outFile1");

    istream_iterator<string> in(is), eof;
    for_each(in, eof, bind(print, ref(cout), _1, '\n'));
    return 0;
}
