
#include <iostream>
#include <string.h>
using namespace std;
int main() {
    int n;
    cout << "Enter a Number" << endl;
    cin >> n;
    int i;
    char *letter = NULL;
    char *result = NULL;
    
    while (n) {
        i = n % 26;
        n = n / 26;
        letter = 64 + i;
        strcat(letter, result);
    }
    cout << result << endl;
    return 0;
}
