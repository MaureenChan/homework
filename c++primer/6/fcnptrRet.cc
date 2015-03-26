#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

string::size_type sumLength(const string&, const string&);
string::size_type largerLength(const string&, const string&);

string::size_type sumLength(const string& s1, const string& s2) {
    return s1.size() + s2.size();
}

string::size_type largerLength(const string& s1, const string& s2) {
    return (s1.size() > s2.size()) ? s1.size() : s2.size();
}

decltype(sumLength) *getFcn(const string&);

auto getFcn(const string&) -> string::size_type(*)(const string&, const string&);

string::size_type (*getFcn(const string&))(const string&, const string&);

decltype(sumLength) *getFcn(const string &fetch) {
    if (fetch == "sum")
        return sumLength;
    return largerLength;
}

int main() {
    cout << getFcn("sum")("hello", "world!") << endl;
    cout << getFcn("larger")("hello", "world!") << endl;

    return 0;
}
