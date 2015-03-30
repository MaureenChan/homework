#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

int main() {
    vector<int> v1 = {1,2,3,4,5,6};
    vector<int> v2 = {1,2,3};
    vector<int> v3 = {1,3};
    vector<int> v4 = {1,2,3,4,5,6};

    if (v1 > v2) {
        cout << "v1 is equal to v2!" << endl;
    }

    if (v3 > v2) {
        cout << "equal!" << endl;
    } else {
        cout << "not equal" << endl;
    }

    if (v4 == v1) {
        cout << "equal!" << endl;
    } else {
        cout << "not equal" << endl;
    }

    return 0;
}
