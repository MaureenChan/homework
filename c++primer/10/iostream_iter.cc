#include "head.h"

int main() {
    istream_iterator<int> int_it(cin);
    istream_iterator<int> int_eof;
    vector<int> v(int_it, int_eof);

    sort(v.begin(), v.end());
    ostream_iterator<int> out(cout, " ");
    unique_copy(v.begin(), v.end(), out);
    cout << endl;
    ofstream out_file("outFile2");
    ostream_iterator<int> out_iter(out_file, " ");
    copy(v.begin(), v.end(), out_iter);
    out_file << endl;
    return 0;
}
