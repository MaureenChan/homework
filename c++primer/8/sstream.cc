#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::istream;
using std::ostream;
using std::endl;

#include <sstream>
using std::ostringstream;
using std::istringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

struct PersonInfo {
    string name;
    vector<string> phones;
};

string format(const string &s) { return s; }
bool valid(const string &s) {
    return true;
}

vector<PersonInfo>
getData(istream &is) {
    string line, word;

    vector<PersonInfo> people;

    while (getline(is, line)) {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;

        while (record >> word) {
            info.phones.push_back(word);
        }

        people.push_back(info);
    }
    return people;
}

ostream& process(ostream &os, vector<PersonInfo> people) {
    for (const auto &entry : people) {
        ostringstream formatted, badNums;
        for (const auto &nums : entry.phones) {
            if (!valid(nums)) {
                badNums << " " << nums;
            } else {
                formatted << " " << format(nums);
            }
        }
        if (badNums.str().empty())
            os << entry.name << " "
                << formatted.str() << endl;
        else 
            cerr << "input error: " << entry.name
                << " invalid number(s) " << badNums.str() << endl;
    }
    return os;
}
int main() {
    process(cout, getData(cin));
    return 0;
}
