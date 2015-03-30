#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

int main() {
    string name("AnnaBelle");
    auto pos1 = name.find("Anna");
    cout << pos1;
    string lowercase("annabelle");
    pos1 = lowercase.find("Anna");
    cout << " " << pos1 << endl;
    return 0;
}
