#include "head.h"

int main() {
    int ia[] = {0,1,2,3,4,5,6,7,8,9};

    int *p = ia;
    ++p;

    int *e = &ia[10];
    for (int *b = ia; b != e; ++b)
        cout << *b << " ";
    cout << endl;

    const size_t sz = 10;
    int arr[sz];

    for (auto &n : arr)
        cin >> n;
    for (auto i : arr)
        cout << i << " ";
    cout << endl;

    int *pbeg = begin(arr), *pend = end(arr);

    while (pbeg != pend && *pbeg >= 0) 
        ++pbeg;
    if (pbeg == pend)
        cout << "no negative elements in arr" << endl;
    else
        cout << " fist negative number was " << *pbeg << endl;
    return 0;



}
