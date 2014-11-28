#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct QNode
{
	int tag;
	struct QNode *next;
}qnode, *ptrqnode;
void print(ptrqnode s)
{
	printf("%d", s->tag);
	printf("\n");
}

void InitLink(ptrqnode s, int monkey_number){
	int i;
	for(i = 2; i <= monkey_number; i++){
		ptrqnode t;
		t = (ptrqnode)malloc(sizeof(qnode));
		t->tag = i;
		t->next = s->next;
		s->next = t;
		s = s->next;
	}
	s = s->next;
}

void select(ptrqnode s, int period){
	int i;
	ptrqnode t;
	if(period == 0){
		print(s);
		return ;
	}
	if(period != 1)
		s = s->next;
	while(1){
		if(s->next == s)
			break;
		for(i = 2; i<= period; i++){
			s = s->next;
		}
		//删除结点
		t = s->next;
		s->next = t->next;
		s = s->next;
		free(t);
	}

	if(s->next == s){
		printf("The King is ");
		print(s);
		printf("\n");
	}
}

int main(){
	int monkey_number, period;
	ptrqnode s;
	printf("monkey_number and period(monkey_number period)");
	scanf("%d %d", &monkey_number, &period);
	s = (ptrqnode)malloc(sizeof(qnode));
	s->tag = 1;
	s->next = s;
	InitLink(s, monkey_number);
	select(s, period);
	system("pause");
	return 0;
}
