#include <stdio.h>
#include <stdlib.h>
typedef struct QNode
{
	int tag;
	struct QNode *next;
}qnode, *ptrqnode;
void print(ptrqnode s)
{
	printf("tag:%d", s->tag);
	printf("\n");
}

void Output(ptrqnode s)
{
	//Output present linklist
	int tag;
	tag = s->tag;
	s = s->next;
	while(tag != s->tag){
		print(s);
		s = s->next;
	}
	print(s);
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
	while(1){
		if(s->next == s)
			break;
		else
			for(i = 2; i < period; i++){
				s = s->next;
			}
		t = s->next;
		s->next = t->next;
		s = s->next;
		free(t);
	}
	if(s->next == s)
		print(s);
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
}
