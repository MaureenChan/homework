#include <iostream>
using namespace std;

#define BORDER 100
 
struct Node {
    int left;
    int right;
    int counter;
}segTree[4 * BORDER];

void construct(int index, int lef, int rig) {
    segTree[index].left = lef;
    segTree[index].right = rig;
    if (lef == rig) {
        segTree[index].counter = 0;
        return ;
    }
    int mid = (lef + rig) >> 1;
    construct((index << 1) + 1, lef, mid);
    construct((index << 1) + 2, mid + 1, rig);
    segTree[index].counter = 0;
}

void insert(int index, int x) {
    ++segTree[index].counter;
    if (segTree[index].left == segTree[index].right) {
        return ;
    }
    int mid = (segTree[index].left + segTree[index].right) >> 1;
    if (x <= mid) {
        insert((index << 1) + 1, x);
    } else {
        insert((index << 1) + 2, x);
    }
}

int query(int index, int left, int right) {
    if (segTree[index].left == left && segTree[index].right == right) {
        return segTree[index].counter;
    }

    int mid = (segTree[index].left + segTree[index].right) >> 1;

    if (right <= mid) {
        return query((index << 1) + 1, left, right);
    } else if (left > mid) {
        return query((index << 1) + 2, left, right);
    }

    return query((index << 1) + 1, left, mid) + query((index << 1) + 2, mid + 1, right);
}

int testPoint[10] = {
    1,4,2,9,48,15,13,44,6,90
};

int main() {
    construct(0, 0, 100);
    int reverseSum = 0;
    for (int i = 0; i < 10; ++i) {
        reverseSum += query(0, testPoint[i], BORDER);
        printf("num of reverse order is : %d \n", reverseSum);
        insert(0, testPoint[i]);
    }
    return 0;
}
