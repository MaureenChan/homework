#include <map>
using std::map;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main() {
    map<string, size_t> word_count;
    string word;
    while (cin >> word) 
        ++word_count[word];

    for (const auto &w : word_count)
        cout << w.first << " occurs " << w.second << " times" << endl;

    auto map_it = word_count.cbegin();

    while (map_it != word_count.cend()) {
        cout << map_it->first << " occurs "
             << map_it->second << " times" << endl;
        ++map_it;
    }

    return 0;
}
