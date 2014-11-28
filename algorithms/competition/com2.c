#include <stdio.h>
#include <math.h>
#include <windows.h>

#define N 65
int a[N][N] = {0};
void timetable(int k);
void print(int np);

int main(){
	int n, np;
	scanf("%d", &n);
	np = pow(2, n);
	timetable(n);
	print(np);
	getchar();
	system("pause");
	
	return 0;
}

void timetable(int k){
	int n, temp, i, j, p, t;
	n = 2;
	a[1][1] = 1;
	a[1][2] = 2;
	a[2][1] = 2;
	a[2][2] = 1;

	for(t = 1; t < k; t++){
		temp = n;
		n = n * 2;
		for(i = temp + 1; i <= n; i++)
			for(j = 1; j<= temp; j++)
				a[i][j] = a[i-temp][j] + temp;
		for(i = 1; i <= temp; i++)
			for(j = temp + 1; j <= n; j++)
				a[i][j] = a[i + temp][(j + temp) % n];
		for(i = temp + 1; i <= n; i++)
			for(j = temp + 1; j <= n; j++)
				a[i][j] = a[i - temp][j - temp];
	}
}
void print(int np){
	int i, j;
	for(i = 1; i<= np; i++){
		printf("%d", a[i][1]);
		for(j = 2; j <= np; j++)
			printf(" %d", a[i][j]);
		printf("\n");
	}
}
