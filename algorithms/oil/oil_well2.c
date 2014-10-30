#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int low, int high){
	int t;
	t = a[low];
	a[low] = a[high];
	a[high] = t;
}

int partition(int *y, int low, int high){
	int pivotkey;
	pivotkey = y[low];
	while(low < high){
		while(low < high && y[high] >= pivotkey){
			high--;
		}
		swap(y, low, high);
		while(low < high && y[low] <= pivotkey){
			low++;
		}
		swap(y, low, high);
	}
	return low;
}

//快排
void QSort(int *a, int low, int high){
	int pivot;
	if(low < high){
		pivot = partition(a, low, high);

		QSort(a, low, pivot - 1);
		QSort(a, pivot + 1, high);
	}
}

int main(){
	int i = 0, sum = 0;
	int ret, length, well;
	int *x, *y;
	//输入
	printf("Please input oil well number:");
	scanf("%d", &well);

	x = (int *)malloc(well * sizeof(int));
	y = (int *)malloc(well * sizeof(int));

	printf("Please input the oil well location:");
	for(i = 0; i < well; i++){
		scanf("%d %d", &x[i], &y[i]);
	}

	QSort(y, 0, well - 1);

	ret = well / 2;

	//距离
	i = 0;
	while(i < well){
		if(y[i] > y[ret]){
			length = y[i] - y[ret];
			sum += length;
		}
		if(y[i] < y[ret]){
			length = y[ret] - y[i];
			sum += length;
		}

		i++;
	}

	//输出
	for(i = 0; i < well; i++){
		printf("%d\t", y[i]);
	}
	printf("sum:%d\n", sum);
	free(x);
	free(y);
	return 0;
}

