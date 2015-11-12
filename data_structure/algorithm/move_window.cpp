#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
using namespace std;


vector <int> move_window(vector<int>& num, unsigned int size) {
    vector<int> res;
    if (size > num.size() || size == 0)
        return res;

    deque<int> dq;
    for (int i = 0; i < size; i++) {
        while (!dq.empty() && num[i] <= dq.back()) {
            dq.pop_back();
        }
        dq.push_back(num[i]);
    }

    res.push_back(dq.front());
    for (int i = size; i < num.size(); ++i) {
        if (num[i - size] == dq.front()) 
            dq.pop_front();
        while (!dq.empty() && num[i] < dq.back()) {
            dq.pop_back();
        }
        dq.push_back(num[i]);
        res.push_back(dq.front());
    }
    return res;
}

void display(vector<int>& num) {
    cout << "The result is:" << endl;
    for (int i = 0; i < num.size(); i++) {
        cout << num[i] << '\t';
    }
    cout << endl;
}

int main() {
    vector<int> num, result;
    string line, linek;
    int k, input;
    cout << "Press Q or Ctrl-C to exit" << endl;
    while (1) {
        cout << "Enter Your Window Size(Bigger than 0):" << endl;
        getline(cin, linek);
        istringstream tstream(linek);
        tstream >> k;
        if (k == 0) {
            break;
        }
        cout << k << endl;
        if (k < 1) {
            cout << "Wrong Size, ReEnter" << endl;
            continue;
        }
        cout << "Enter Your Number Sequence:" << endl;
        getline(cin, line);
        istringstream stream(line);
        while (stream >> input) {
            num.push_back(input);
        }

        if (k > num.size()) {
            cout << "Your Sequence is too Small!, ReEnter" << endl;
            continue;
        }
        result = move_window(num, k);
        display(result);
        cout << "**************************************************************************" << endl;
        cout << '\n' << '\n' << endl;
    }


    return 0;

}
