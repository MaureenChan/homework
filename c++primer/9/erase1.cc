#include <algorithm>
using std::find;

#include <string>
using std::string;

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main() {
    list<string>slist;
    string s;
    while (cin >> s) 
        slist.push_back(s);

    auto iter = find(slist.begin(), slist.end(), "Quasimodo");
    if (iter != slist.end()) 
        slist.erase(iter);

    auto orig = slist;
    slist.clear();
    cout << "after clear, size is : " << slist.size() << endl;

    slist = orig;
    auto elem1 = slist.begin(), elem2 = slist.end();

    elem1 = slist.erase(elem1, elem2);
    cout << "after erase elem1 to elem2 size is : " << slist.size() << endl;

    if (elem1 != elem2)
        cout << "somethings wrong" << endl;
    else
        cout << "okey, they're equal " << endl;

}



