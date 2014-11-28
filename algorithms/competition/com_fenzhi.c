#include <stdio.h>
#include <math.h>
#include <windows.h>

#define N 65
int arr[N][N] = {0};
void timetable(int np);
void copy(int np);
void print(int np);

int main(){
	int n, np;
	scanf("%d", &n);
	np = pow(2, n);
	timetable(np);
	print(np);
	system("pause");
	return 0;
}

void timetable(int np){
	if(np == 1){
		arr[1][1] = 1;
	}
	else{
		timetable(np/2);
		copy(np);
	}
}

void copy(int np){
	int k = np / 2;
	int i, j;
	for(i = 1; i <= k; i++){		//i control row
		for(j = 1; j <= k; j++){	//j control column
			arr[i][j + k] = arr[i][j] + k;
			arr[i + k][j] = arr[i][j] + k;
			arr[i + k][j + k] = arr[i][j];
		}
	}
}

void print(int np){
	int i, j;
	for(i = 1; i<= np; i++){
		printf("%d", arr[i][1]);
		for(j = 2; j <= np; j++)
			printf(" %d", arr[i][j]);
		printf("\n");
	}
}
