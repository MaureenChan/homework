#include <stdio.h>
#include <stdlib.h>

typedef struct QNode
{
	int tag;
	int flag;
	struct QNode *next;
}qnode, *ptrqnode;
void print(ptrqnode s)
{
	printf("tag:%d", s->tag);
	printf("\tflag:%d", s->flag);
	printf("\n");
}
void InitLink(ptrqnode s, int holenumber)
{
	int i;
	for(i = 2; i <= holenumber; i++)
	{
		ptrqnode t;
		t = (ptrqnode)malloc(sizeof(qnode));
		t->tag = i;
		t->flag = 0;
		t->next = s->next;
		s->next = t;
		s = s->next;
	}
	s->flag = 1;
}
void Output(ptrqnode s)
{
	int tag;
	tag = s->tag;
	print(s);
	s = s->next;
	while(tag != s->tag)
	{
		print(s);
		s = s->next;
	}
}
void catch(ptrqnode s, int catch_number)
{
	int i, k;
	for(i = 1; i <= catch_number; i++)
	{
		for(k = 0; k <= i; k++)
		{
			s = s->next;
		}
		if(s->flag != 1)
			s->flag = 1;
	}
}
void find(ptrqnode s)
{
	int tag;
	tag = s->tag;
	s = s->next;
	while(tag != s->tag)
	{
		if(s->flag == 0)
			print(s);
		s = s->next;
	}

}
int main()
{
	ptrqnode s;
	int holenumber;
	int catch_number;
	printf("Please input holenumber:");
	scanf("%d", &holenumber);
	printf("Please input catch_number:");
	scanf("%d", &catch_number);
	s = (ptrqnode)malloc(sizeof(qnode));
	s->tag = 1;
	s->flag = 1;
	s->next = s;
	InitLink(s, holenumber);
	catch(s, catch_number);
	find(s);
	return 0;
}
