#include <map>
using std::map;

#include <string>
using std::string;

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
        ++word_count.insert({word, 0}).first->second;
    
    for (auto it = word_count.cbegin(); it != word_count.cend(); ++it) {
        auto w = *it;
        cout << w.first << " occurs " << w.second << " times" << endl;
    }

    auto map_it = word_count.cbegin();

    while (map_it != word_count.cend()) {
        cout << map_it->first << " occurs"
             << map_it->second << " times" << endl;
        ++map_it;
    }

    return 0;
}
