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

//构造一个圈
void InitLink(ptrqnode s, int number){
	int i;
	for(i = 2; i <= number; i++){
		ptrqnode t;
		t = (ptrqnode)malloc(sizeof(qnode));
		t->tag = i;
		t->next = s->next;
		s->next = t;
		s = s->next;
	}
	s = s->next;
}

//删除循环链表，将每次删除的人进栈
ptrqnode Out_of_circle(ptrqnode circle, int s, int m){
	int i;
	//Init a linklist
	ptrqnode select;
	ptrqnode q,t;
	select = (ptrqnode)malloc(sizeof(int));
	select->tag = 0;
	select->next = NULL;
	q = select;

	//计算第s个人
	for (i = 1; i < s; i++){
		circle = circle->next;
	}

	//计算念到m的人，从循环链表上删除
	while(circle->next != circle){
		for(i = 2; i < m; i++){
			circle = circle->next;
		}
		t = circle->next;
		circle->next = t->next;
		circle = circle->next;

		//删除的人进栈
		q->next = t;
		t->next = NULL;
		q = q->next;
	}
	q->next = circle;
	circle->next = NULL;
	return select;
}

int main(){
	int n, s, m;
	ptrqnode circle;
	ptrqnode select, q;
	
	//输入
	printf("Please input people number:\t");
	scanf("%d", &n);
	printf("Please input s(s>0):\t");
	scanf("%d", &s);
	printf("Please input period\t");
	scanf("%d", &m);
	
	//构造圈
	circle = (ptrqnode)malloc(sizeof(qnode));
	circle->tag = 1;
	circle->next = circle;

	InitLink(circle, n);

	//得到出圈序列
	select = Out_of_circle(circle, s, m);
	q = select->next;
	while(q->next){
		print(q);
		q = q->next;
	}
	print(q);

	return 0;
}
