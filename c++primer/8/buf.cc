#include <iostream>

using std::endl;
using std::flush;
using std::ends;
using std::unitbuf;
using std::nounitbuf;
using std::cout;


int main() {
    cout << "hi!" << endl;
    cout << "hi!" << flush;
    cout << "hi!" << ends;

    cout << unitbuf;

    cout << "first" << " second " << endl;

    cout << nounitbuf;

    return 0;
}
