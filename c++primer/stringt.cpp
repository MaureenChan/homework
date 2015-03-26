#include <iostream>
#include <cctype>
#include <string>
using namespace std;

int main() {
    string word;
    string line;
    //while (cin >> word) 
        //cout << word <<endl;

    //while (getline(cin, line)) 
        //cout << line <<endl;

    string str("some string");
    int punct_cnt = 0;
    for (auto &c : str)
        c = toupper(c);

    cout << str[0] << endl;

        //if (ispunct(c))
            //++punct_cnt;

    //cout << " "
        //<< punct_cnt
        //<< " puctiuaction characters in " 
        //<< str
        //<< endl;

        //cout << c << endl;
    return 0;
}
