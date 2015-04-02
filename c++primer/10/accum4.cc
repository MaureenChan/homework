#include <numeric>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
    istream_iterator<int> in(cin), eof;
    cout << accumulate(in, eof, 0) << endl;
    return 0;
}
