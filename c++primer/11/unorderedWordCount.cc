#include <unordered_map>
using std::unordered_map;

#include <unordered_set>
using std::unordered_set;
using std::unordered_multiset;

#include <string>
using std::string;

using std::hash;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cstddef>
using std::size_t;

#include "Sales_data.h"

int main() {
    unordered_map<string ,size_t> word_count;
    string word;
    while (cin >> word)
        ++word_count[word];

    for (const auto &w : word_count)
        cout << w.first << " occurs " << w.second
             << ((w.second > 1) ? " times" : " time") << endl;

    return 0;
}

size_t hasher(const Sales_data &sd) {
    return hash<string>()(sd.isbn());
}

bool eqOp(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() == rhs.isbn();
}

using SD_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>;

SD_multiset bookstore(42, hasher, eqOp);

struct Foo { string s; };

bool operator==(const Foo &l, const Foo&r) { return l.s == r.s; }

size_t FooHash(const Foo &f) { 
    return hash<string>() (f, s);
}

unordered_set<Foo, decltype(FooHash)*> fooSet(10, FooHash);

