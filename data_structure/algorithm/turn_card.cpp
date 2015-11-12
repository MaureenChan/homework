#include <cstdio>
#include <cstring>
#include <iostream>
#define MAX 1005
using namespace std;

int tree[MAX][MAX];
int x, n, t, res;
char cmd;
int x1, y1, x2, y2;

int lowbit(int i) {
    return i & (-i);
}

void display(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << tree[i][j] % 2 << '\t';
        }
        cout << endl;
    }
}

void add(int a, int b, int d) {
    for (int i = a; i <= n; i += lowbit(i)) 
        for (int j = b; j <= n; j += lowbit(j))
            tree[i][j] += d;
    return ;
}

int getsum(int a, int b) {
    int sum = 0; 
    for (int i = a; i > 0; i -= lowbit(i))
        for (int j = b; j > 0; j -= lowbit(j))
            sum += tree[i][j];
    return sum;
}


int main() {
    printf("Please Press Ctrl-C to exit\n");
    while (1) {
        // 初始化数组
        memset(tree, 0, sizeof(tree));
        // 输入数组的大小 N
        printf("Please Enter Matrix Size:\n");
        scanf("%d", &n);
        while(1) {
            printf("Please Enter Your Command:\n");
            printf("C: Turn Card\n");   // 翻卡
            printf("Q: Check Card\n");  // 查看卡的状态
            printf("D: Display Tree\n");// 查看树
            printf("N: Create a New Tree\n"); // 创建新的树
            scanf("\n%c", &cmd);
            if (cmd == 'C' || cmd == 'c') {
                // 输入两个点，(x1, y1)为左上角的点 (x2, y2)为右上角的点
                printf("Please Enter an Enclosure:(x1 y1 x2 y2)\n");
                printf("(x1, y1) represent left top corner\n");
                printf("(x2, y2) represent right bottom corner\n");
                printf("1 <= x1 <= x2 <= n, 1 <= y1 <= y2 <= n\n");
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                // 根据点划分区域进行计算
                add(x1, y1, 1);
                add(x1, y2 + 1, -1);
                add(x2 + 1, y1, -1);
                add(x2 + 1, y2 + 1, 1);
            } else if (cmd == 'Q' || cmd == 'q') {
                // 输入一个点的位置查看卡的状态
                printf("Please Enter the Card Position:(x, y)\n");
                scanf("%d %d", &x1, &y1);
                res = getsum(x1, y1) % 2;
                printf("Status is %d\n", res);
            } else if (cmd == 'D' || cmd == 'd') {
                // 查看数组
                display(n);
            } else if (cmd == 'N' || cmd == 'n') {
                // 退出循环，重新初始化数组
                break;
            }
            printf("***************************************************\n");
        }
        printf("***************************************************\n");
        printf("\n");
    }
    return 0;
}
