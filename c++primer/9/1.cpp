#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main() {
    string word;
    vector<string> container;
    while (cin >> word) {
        container.push_back(word);
        if (word.size() > 4) {
            cout << word.size() << endl;
            word.push_back('s');
        }
    }

    for (auto i : container) 
        cout << i << endl;
}
