#include <algorithm>
using std::find;
#include <string>
using std::string;
#include <list>
using std::list;

#include <forward_list>
using std::forward_list;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

int main() {
    list<int> lst = {0,1,2,3,4,5,6,7,8,9};
    cout << "initial list: ";
    for (auto it : lst) 
        cout << it << " ";
    cout << endl;
    cout << "initial size: " << lst.size() << endl;

    auto it = lst.begin();
    while (it != lst.end())
        if (*it % 2) 
            it = lst.erase(it);
        else
            ++it;

    cout << "after erasing size: " << lst.size() << endl;
    cout << "after erasing odd elements from lst: ";
    for (auto it : lst)
        cout << it << " ";
    cout << endl;
    forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};

    cout << "initial list: ";
    for (auto it : flst) 
        cout << it << " ";
    cout << endl;

    auto prev = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end()) {
        if (*curr % 2) 
            curr = flst.erase_after(prev);
        else {
            prev = curr;
            ++curr;
        }
    }

    cout << "after erasing elements from flst:";
    for (auto it : flst)
        cout << it << " ";
    cout << endl;

    return 0;

}
