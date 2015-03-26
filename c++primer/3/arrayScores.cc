#include <cstddef>
using std::size_t;

#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main() {
    vector<unsigned> grades;

    unsigned scores[11] = {};
    unsigned grade;

    while (cin >> grade) {
        if (grade <= 100) 
            ++scores[grade / 10];
        grades.push_back(grade);
    }

    cout << "grades.size = " << grades.size() << endl;

    for (auto g : grades) 
        cout << g << " ";
    cout << endl;

    for (auto i : scores) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
