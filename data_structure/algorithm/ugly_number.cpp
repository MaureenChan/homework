#define LL long long 
#include<stdio.h>
#include<queue>
LL hum[10000];
LL cn = 1;
using namespace std;

void ugly_number() {
    priority_queue<LL, vector<LL>, greater<LL>> q;
    q.push(2);
    q.push(3);
    q.push(5);
    q.push(7);
    hum[1] = 1;
    LL a = q.top();
    q.pop();

    while (a <= 2000000000) {
        if (a != hum[cn]) {
            hum[++cn] = a;
            q.push(a * 2);
            q.push(a * 3);
            q.push(a * 5);
            q.push(a * 7);
        }
        a = q.top();
        q.pop();
    }
    return ;
}

int main() {
    ugly_number();
    int n;
    while (scanf("%d", &n) != EOF && n != 0) {
        printf("The %d", n);
        if (n % 100 == 11 || n % 100 == 12 || n % 100 == 13)
            printf("th ");
        else if (n % 10 == 1) 
            printf("st ");
        else if (n % 10 == 2) 
            printf("nd ");
        else if (n % 10 == 3) 
            printf("rd ");
        else 
            printf("th ");
        printf("humble number is %lld.\n", hum[n]);
    }
    return 0;
}
