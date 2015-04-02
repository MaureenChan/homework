#include "head.h"

void elimDups(vector<string> &words) {
    sort(words.begin(), words.end());
    for_each(words.begin(), words.end(),
            [](const string &s) { cout << s << " "; });
    cout << endl;

    auto end_unique = unique(words.begin(), words.end());
    for_each(words.begin(), words.end(), 
            [](const string &s) { cout << s << " "; });
    cout << endl;

    words.erase(end_unique, words.end());
    for_each(words.begin(), words.end(),
            [](const string &s) { cout << s << " " });
    cout << endl;
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    stable_sort(words.begin(), words.end(),
            [](const string &a, const string &b) 
            { return a.size() < b.size(); });

    auto wc = find_if(words.begin(), words.end(), 
            [sz](const string &a)
            { return a.size() > sz; });

    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s")
         << " of length " << sz << " or longer" << endl;

    for_each(wc, words.end(), 
            [](const string &s) {cout << s << " "; });
    cout << endl;

}

bool check_size(const string &s, string::size_type sz) {
    return s.size() >= sz;
}

int main() {
    vector<string> words;

    string next_word;
    while (cin >> next_word) {
        words.push_back(next_word);
    }

    biggies(words, 5);

    size_t sz = 5;

    auto wc = find_if(words.begin(), words.end(), 
              bind(check_size, std::placeholders::_1, sz));
    auto count = words.end() - wc;
    cout << cout << " " << make_plural(count, "word", "s")
         << " of length " << sz << " or longer" << endl;

    return 0;
}
