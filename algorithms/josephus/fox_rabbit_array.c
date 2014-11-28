#include <stdio.h>
#include <windows.h>
#define N 1000


int main()
{
	int i;
	int t = 0;
	int holes[10] = {0};
	holes[0] = 1;
	holes[1] = 1;
	for(i = 0; i <= N; i++)
	{
		t = t + i;
		holes[t % 10] = 1;
	}

	for(i = 0; i < 10; i++)
		if(holes[i] == 0)
			printf("%d\t", i);
	printf("\n");
	getchar();
	system("pause");
	return 0;
}
