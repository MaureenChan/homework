#include <stdio.h>
#include <stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))
struct pcb {
	char name;
	char state;
	int super;
	int atime;	//arrive time
	int ntime;	//need time
	int rtime;	//run time
	struct pcb *link;
}*ready = NULL, *p;
int time = 0;
typedef struct pcb PCB;
void input();
void sort();
int space();
void disp(PCB *pr);
void check();
void del_pcb();
void running();

void del_pcb(){
	printf("\n 进程 [%c] 已完成.\n", p->name);
	free(p);
}
void sort(){
	PCB *first, *second;
	int insert = 0;
	if((ready == NULL) || ((p->atime) < (ready->atime))){
		p->link = ready;
		ready = p;
	}else{
		first = ready;
		second = first->link;
		while(second != NULL){
			if((p->atime) < (second->atime)){
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
	printf("\n **** 当前正在运行的进程是:%c", p->name);
	disp(p);
	pr = ready;
	printf("\n ****当前就绪队列的状态为:\n");
	while(pr != NULL){
		disp(pr);
		pr = pr->link;
	}
}
void disp(PCB *pr){
	printf("\n qname\t state \t super \t atime \t ndtime\t runtime \n");
	printf("|%c\t", pr->name);
	printf("|%c\t", pr->state);
	printf("|%d\t", pr->super);
	printf("|%d\t", pr->atime);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("\n");
}

void input(){
	int i = 0, num = 4;
	p = getpch(PCB);
	p->name = '1';
	p->super = 2;
	p->ntime = 10;
	p->state = 'w';
	p->rtime = 0;
	p->atime = 0;
	p->link = NULL;
	sort();
	p = getpch(PCB);
	p->name = '2';
	p->super = 3;
	p->ntime = 5;
	p->state = 'w';
	p->rtime = 0;
	p->atime = 4;
	p->link = NULL;
	sort();
	p = getpch(PCB);
	p->name = '3';
	p->super = 7;
	p->ntime = 7;
	p->state = 'w';
	p->rtime = 0;
	p->atime = 6;
	p->link = NULL;
	sort();
	p = getpch(PCB);
	p->name = '4';
	p->super = 2;
	p->ntime = 2;
	p->state = 'w';
	p->rtime = 0;
	p->atime = 9;
	p->link = NULL;
	sort();
	
	/*int j = 6;*/
	/*for(i = 0; i < num; j--){*/
		/*p = getpch(PCB);*/
		/*p->name = i;*/
		/*p->super = i;*/
		/*p->ntime = j + i;*/
		/*p->rtime = 0;*/
		/*p->state = 'w';*/
		/*p->link = NULL;*/
		/*sort();*/
	/*}*/
}

void running(){
	(p->rtime)++;
	if(p->rtime == p->ntime)
		del_pcb();
	/*else{*/
		/*p->state = 'w';*/
		/*sort();*/
	/*}*/
}


int main(){
	int len;
	char ch;
	input();
	len = space();
	while((len != 0) && (ready != NULL)){
		ch = getchar();
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
