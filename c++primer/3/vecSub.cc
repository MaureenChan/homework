#include "head.h"

int main() {
    vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    auto sz = v.size();
    decltype(sz) i = 0;

    while (i != sz) {
        v.push_back(*v.begin() + i);
        ++i;
    }

    for (auto it : v)
        cout << it << " ";
    cout << endl;

    vector<int> alt_v = {0,1,2,3,4,5,6,7,8,9};
    for (decltype(alt_v.size()) i = 0, sz = alt_v.size(); i != sz; ++i)
        alt_v.push_back(alt_v[i]);

    for (auto it : alt_v)
        cout << it << " ";
    cout << endl;
    vector<int> v2 = {0,1,2,3,4,5,6,7,8,9};
    decltype(v2.size()) ix = 0;
    while (ix != v2.size() && v2[ix] < 5) {
        v2[ix] = 0;
        ++ix;
    }

    for (unsigned i = 0; i != v2.size(); i++)
        cout << v2[i] << " ";
    cout << endl;

    vector<int> alt_v2 = {0,1,2,3,4,5,6,7,8,9};
    auto it = alt_v2.begin();
    while (it != alt_v2.end() && *it < 5) {
        *it = 0; 
        ++it;
    }

    for (auto it = alt_v2.begin(); it != alt_v2.end(); ++it)
        cout << *it << " ";
    cout << endl;
    return 0;

}
