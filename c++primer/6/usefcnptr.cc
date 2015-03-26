#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int min_element(
        vector<int>::iterator,
        vector<int>::iterator);

int (*pf)(vector<int>::iterator, vector<int>::iterator) = min_element;

int main() {
    vector<int> ivec = {1,2,-3,4,5,6,7,8};
    cout << "Direct call: "
         << min_element(ivec.begin(), ivec.end()) << endl;
    cout << "Indirect call: "
         << pf(ivec.begin(), ivec.end()) << endl;

    cout << "equivalent indirect call: "
         << (*pf)(ivec.begin(), ivec.end()) << endl;

    return 0;
}

int min_element(
        vector<int>::iterator beg,
        vector<int>::iterator end) {
    int minVal = 0;
    while (beg != end) {
        if (minVal > *beg) 
            minVal = *beg;
        ++beg;
    }
    return minVal;
}
