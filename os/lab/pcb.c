#include <stdio.h>
#include <stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))
struct pcb {
	char name[10];
	char state;
	int super;
	int ntime;
	int rtime;
	struct pcb *link;
}*ready = NULL, *p;

typedef struct pcb PCB;
void input();
void sort();
int space();
void disp(PCB *pr);
void check();
void del_pcb();
void running();


void del_pcb(){
	printf("\n 进程 [%s] 已完成.\n", p->name);
	free(p);
}

void input() {
	int i, num;
	printf("\n Please input PCB num:");
	scanf("%d", &num);
	for(i = 0; i < num; i++){
		printf("\n 进程号 No.%d:\n", i);
		p = getpch(PCB);
		printf("\n 输入进程名:");
		scanf("%s", p->name);
		printf("\n 输入进程优先数:");
		scanf("%d", &p->super);
		printf("\n 输入进程运行时间:");
		scanf("%d", &p->ntime);
		printf("\n");
		p->rtime = 0;
		p->state = 'w';
		p->link = NULL;
		sort();
	}
}

void sort() {
	PCB *first, *second;
	int insert = 0;

	if((ready == NULL) || ((p->super) > (ready->super))){
		p->link = ready;
		ready = p;
	}else{
		first = ready;
		second = first->link;

		while(second != NULL){
			if((p->super) > (second->super)){
				p->link = second;
				first->link = p;
				second = NULL;
				insert = 1;
			}else{
				first = first->link;
				second = second->link;
			}
		}

		if(insert == 0)
			first->link = p;
	}
}

int space(){
	int l = 0;
	PCB *pr = ready;
	while(pr != NULL){
		l++;
		pr = pr->link;
	}
	return l;
}

void check(){
	PCB *pr;
	printf("\n **** 当前正在运行的进程是:%s", p->name);
	disp(p);
	pr = ready;
	printf("\n ****当前就绪队列的状态为:\n");
	while(pr != NULL){
		disp(pr);
		pr = pr->link;
	}
}

void disp(PCB *pr){
	printf("\n qname\t state \t super \t ndtime\t runtime \n");
	printf("|%s\t", pr->name);
	printf("|%c\t", pr->state);
	printf("|%d\t", pr->super);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("\n");
}

void running(){
	(p->rtime)++;
	if(p->rtime == p->ntime)
		del_pcb();
	else{
		(p->super)--;
		p->state = 'w';
		sort();
	}
}
int main() {
	int len, h = 0;
	char ch;
	input();
	len = space();
	while((len != 0) && (ready != NULL)){
		ch = getchar();
		h++;
		printf("\n The execute number: %d \n", h);
		p = ready;
		ready = p->link;
		p->state = 'R';
		check();
		running();
		printf("\n 按任一键继续");
		ch = getchar();
	}
	printf("\n\n 进程已经完成.\n");
	ch = getchar();
	return 0;
}
