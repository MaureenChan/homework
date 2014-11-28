#include<stdio.h>
#include<math.h>
#include<stdlib.h>


//二阶矩阵相乘
void Matrix_Multiply(int **A, int **B, int **C) { 
	int i, j, t;
     for(i = 0; i < 2; i++) {  
        for(j = 0; j < 2; j++) {  
           C[i][j] = 0;        
           for(t = 0; t < 2; t++) {  
              C[i][j] = C[i][j] + A[i][t] * B[t][j];          
           }    
        }          
     }  
}  

//矩阵加法：
void add(int n, int **A, int **B, int **R)
{ 
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            R[i][j] = A[i][j] + B[i][j];
}

//矩阵减法：
void sub(int n, int **A, int **B, int **R)
{ 
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            R[i][j] = A[i][j] - B[i][j];
}
void strassen(int n, int **A, int **B, int **C)
{
    int i, j;
    int A11[n][n], A12[n][n], A21[n][n], A22[n][n];
    int B11[n][n], B12[n][n], B21[n][n], B22[n][n];
    int C11[n][n], C12[n][n], C21[n][n], C22[n][n];
    int AA[n][n], BB[n][n];
    int M1[n][n], M2[n][n], M3[n][n], M4[n][n], M5[n][n], M6[n][n], M7[n][n];
    if(n == 2) {
        Matrix_Multiply(**A, **B, **C);
    } else {
        for(i = 0; i < n / 2; i++) {
            for(j = 0; j < n / 2; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n / 2];
                A21[i][j] = A[i + n / 2][j];
                A22[i][j] = A[i + n / 2][j + n / 2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n / 2];
                B21[i][j] = B[i + n /2][j];
                B22[i][j] = B[i + n /2][j + n / 2];
            }
        }

        sub(n / 2, **B12, **B22, **BB);
        strassen(n / 2, **A11, **BB, **M1);

        add(n / 2, **A11,**A12, **AA);
        strassen(n / 2, **AA, **B22, **M2);

        add(n / 2, **A21, **A22, **AA);
        strassen(n / 2, **AA, **B11, **M3);

        sub(n / 2, **B21, **B11, **BB);
        strassen(n / 2, **A22, **BB, **M4);

        add(n / 2, **A11, **A22, **AA);
        add(n / 2, **B11, **B22, **BB);
        strassen(n / 2, **AA, **BB, **M5);

        sub(n / 2, **A12, **A22, **AA);
        add(n / 2, **B21, **B22, **BB);
        strassen(n / 2, **AA, **BB, **M6);

        sub(n / 2, **A11, **A21, **AA);
        add(n / 2, **B11, **B12, **BB);
        strassen(n / 2, **AA, **BB, **M7);

        //C11 = M5 + M4 - M2 + M6
        add(n / 2, **M5, **M4, **AA);
        sub(n / 2, **M6, **M2, **BB);
        add(n / 2, **AA, **BB, **C11);

        //C12 = M1 + M2
        add(n / 2, **M1, **M2, **C12);

        //C21 = M3 + M4
        add(n / 2, **M3, **M4, **C21);

        //C22 = M5 + M1 - M3 - M7
        sub(n / 2, **M5, **M3, **AA);
        sub(n / 2, **M1, **M7, **BB);
        add(n / 2, **AA, **BB, **C22);

         for(i = 0; i < n / 2; i++) {  
           for(j = 0; j < n / 2; j++) {  
              C[i][j] = C11[i][j];  
              C[i][j + n / 2] = C12[i][j];  
              C[i + n / 2][j] = C21[i][j];  
              C[i + n / 2][j + n / 2] = C22[i][j];          
           }          
        } 
    }
}

int main(void)
{
	int **A, **B, **C;
	int a, b, c, m, n, q;
	int i, j;
	a = (int)malloc(sizeof(int));
	b = (int)malloc(sizeof(int));
	c = (int)malloc(sizeof(int));

	printf("enter A array dimension:a b:");
	scanf("%d %d", &a, &b);
	printf("enter B array dimension:b c:");
	scanf("%d %d", &b, &c);
	m = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);

	q =(int)sqrt(m);

	n =(int)pow(2, q + 1);


	A =(int**)malloc(n * sizeof(int));
	B =(int**)malloc(n * sizeof(int));
	C =(int**)malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		A[i] = (int *)malloc(n * sizeof(int));
		B[i] = (int *)malloc(n * sizeof(int));
		C[i] = (int *)malloc(n * sizeof(int));
	}


	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++){
			A[i][j] = 0;
			B[i][j] = 0;
		}


	
    printf("input A: \n");
    for(i = 0; i < a; i++)
        for(j = 0; j < b; j++)
            scanf("%d", &A[i][j]);
    printf("input B: \n");
    for(i = 0; i < b; i++)
        for(j = 0; j < c; j++)
            scanf("%d", &B[i][j]);
    strassen(n, **A, **B, **C);
    printf("C:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
            if(j > 0 && j % (n - 1) == 0)
                printf("\n");
        }
    return 0;
}
