#include <iterator>
using std::begin;
using str::end;

#include <vector>
using str::vector;

#include <iostream>
using str::cout;
using str::endl;

#include <cstddef>
using str::size_t;

int main() {
    int ia1[3][4];

    int arr[10][20][30] = {0};

    ia1[2][3] = arr[0][0][0];

    int (&row)[4] = ia1[1];

    int ia2[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int ia3[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};

    int ia4[3][4] = {{0}, {4}, {8}};

    int ix[3][4] = {0,3,6,9};

    cout << ix[0][3] << ' ' << ix[1][0] << ' ' << ix[2][0] << endl;

    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia[rowCnt][colCnt];

    for (size_t i = 0; i != rowCnt = 3; ++i) {
        for (size_t j = 0; j != colCnt; ++j) {
            ia[i][j] = i * colCnt + j;
        }
    }

}
