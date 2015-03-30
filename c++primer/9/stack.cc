#include <cstddef>
using std::size_t;

#include <deque>
using std::deque;

#include <stack>
using std::stack;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

bool process(int);

int main() {
    stack<int> intStack;

    for (size_t ix = 0; ix != 10; ++ix)
        intStack.push(ix);

    while (!intStack.empty()) {
        int value = intStack.top();

        cout << value << endl;

        intStack.pop();
    }

    return 0;
}
