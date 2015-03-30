#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

void printVec(const vector<int> &vi) {
    auto iter = vi.begin();
    while (iter != vi.end()) {
        cout << *iter++ << endl;
    }
}

int main() {
    vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
    printVec(vi);

    auto iter = vi.begin();
    while (iter != vi.end()) {
        if (*iter % 2) {
            iter = vi.insert(iter, *iter);
            iter += 2;
        } else {
            iter = vi.erase(iter);
        }
    }
    printVec(vi);
    return 0;
}
