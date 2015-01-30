
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef char TElemType;

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTNode, *BiTree;


typedef BiTree SElemType;

typedef struct Stack{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
#define STACK_INIT_SIZE 20
#define STACKINCREASEMENT 10
#define BIANLIANG_MAX 20
#define STR_MAX 60

//��ű������ܵ�����һ�����
int combination[BIANLIANG_MAX];    
//��ʼ��ջ
Status InitStack(SqStack *S)
{
    S->base = (BiTree *)malloc(STACK_INIT_SIZE*sizeof(BiTNode));
    if(!S->base)
	return ERROR;
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}
Status GetTop(SqStack S, BiTree *e)
{
    if(S.top == S.base)
	return ERROR;
    *e = *(S.top - 1);
    return OK;
}
Status Push(SqStack *S, BiTree e)
{
    if(S->top - S->base >= S->stacksize)
	return ERROR;
    *S->top = e;
    S->top++;
    return OK;
}
Status Pop(SqStack *S, BiTree *e)
{
    if(S->top == S->base)
	return ERROR;
    S->top--;
    *e = *(S->top);
    return OK;
}
void PreOrderTraverse(BiTree T)
{
    if(T == NULL)
	return ;
    printf("%2c", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

char priority(char line, char row)
{
    int i,j;
    char priority[7][7] = {' ', '|', '&', '~', '(', ')', '#',
			   '|', '>', '<', '<', '<', '>', '>',
			   '&', '>', '>', '<', '<', '>', '>',
			   '~', '>', '>', '>', '<', '>', '>',
			   '(', '<', '<', '<', '<', '=', ' ', 
			   ')', '>', '>', '>', ' ', '>', '>',
			   '#', '<', '<', '<', '<', ' ', '='
    };

    for (i = 0; i < 7; i++)
	if(priority[0][i] == line)
	    break;
    for (j = 0; j < 7; j++)
	if (priority[j][0] == row)
	    break;
    return priority[j][i];
}

void creatcombination(int n, int m)
{
    int i, num = 0, j = 0, e;
    int temp[BIANLIANG_MAX];
    for(i = 0; i < m; i++)
	combination[i] = 0;
    while (n)
    {
	e = n % 2;
	num++;
	temp[j++] = e;
	n = n / 2;
    }
    j = j - 1;
    num = m - num;
    while (j >= 0)
    {
	e = temp[j--];
	combination[num++] = e;
    }
}

void create(BiTree *tree, BiTree l, BiTree r)
{
    (*tree)->lchild = l;    //ƴ�����Һ���
    (*tree)->rchild = r;
    if(l&&r)	//����Ҷ�ӽ������Һ����ÿ�
    {
	if(l->data >= 65 && l->data <= 90)
	{
	    l->lchild = NULL;
	    l->rchild = NULL;
	}
	if(r->data >= 65 && r->data <= 90)
	{
	    r->lchild = NULL;
	    r->rchild = NULL;
	}
    }
}

void creattree(char s[], BiTree *T)
{
    SqStack variable;	//����ջ
    SqStack logic;	//�����ջ
    BiTree e;		//��������ջջ�����
    BiTree logic_di;	//�����ջջ��
    BiTree variables;	//����ջջ��
    BiTree logics;	//push����
    BiTree kuohao;
    BiTree boot_tree;
    BiTree a,b;
    InitStack(&variable);
    InitStack(&logic);
    logic_di = (BiTree)malloc(sizeof(BiTNode));
    logic_di->data = '#';
    Push(&logic, logic_di);
    while(*s)
    {
	if(*s >= 65 && *s <= 90)
	{
	    variables = (BiTree)malloc(sizeof(BiTNode));
	    variables->data = *s;
	    Push(&variable, variables);
	}
	else if(*s > 90 || *s < 65)
	{
	    GetTop(logic, &e);
	    switch(priority(*s,e->data))
	    {
		case '<':
		    logics = (BiTree)malloc(sizeof(BiTNode));
		    logics->data = *s;
		    Push(&logic,logics);
		    break;
		case '=':
		    Pop(&logic,&kuohao);
		    break;
		case '>':
		    Pop(&logic, &boot_tree);
		    Pop(&variable,&a);
		    b = NULL;
		    if(boot_tree->data != '~')
			Pop(&variable,&b);

		    create(&boot_tree,b,a); //��������
		    Push(&variable,boot_tree);	//������ѹջ
		    if(*s != '#' && *s != ')')
		    {
			logics = (BiTree)malloc(sizeof(BiTNode));
			logics->data = *s;
			Push(&logic, logics);
		    }
		    else
			s = s - 1;
		    break;
	    }
	}
	s++;
    }
    *T = boot_tree;
}

int value_tree(BiTree T)
{
    if(!T)
	return 0;
    else if(T->data != '|' && T->data != '&' && T->data != '~')
	return combination[T->data - 65];  //ֱ�ӷ���Ҷ�ӽ���ֵ
    else if(T->data < 65 || T->data > 90)
	switch(T->data)	//�������ǵ�ֵ
	{
	    case '|':
		return(value_tree(T->lchild) || value_tree(T->rchild));
	    case '&':
		return(value_tree(T->lchild) && value_tree(T->rchild));
	    case '~':
		return(!value_tree(T->rchild));
	}
}

void user(int n)
{
    int i;
    printf("Enter all variable number:\n");
    for ( i = 65; i < 65 + n; i++)
    {
	printf("%c = ", i);
	scanf("%d", &combination[i - 65]);
    }
}
void InitBiTree(BiTree *T)
{
   T = NULL; 
}
int main()
{
    BiTree T;
    //�������
    int sum;	//������ʾ�ܹ���ʾ�������
    int i = 0;		//ѭ��
    int result = 0;	//�����ж�����ʽ���
    int choose,choice;	//����ѡ��
    int n;		//������ʾ��������
    char str[STR_MAX], string[STR_MAX], *pstr;	//�洢�ַ���
    InitBiTree(&T);
    printf("EnterVariable NUMber:\n");
    scanf("%d", &n);
    sum = pow(2,n);	//�����ܹ��������
    //�����ַ���
    printf("Enter Expression:\n");
    scanf("%s", str);
    pstr = str;
    for (; *pstr; pstr++)
	if(*pstr != ' ')    //ɾ���ո�
	    string[i++] = *pstr;
    string[i] = '#';	//��������жϽ������
    string[i + 1] = '\0';
    
    while(1)
    {
	printf("************          ��ѡ����Ҫ�Ĳ���        **********\n");
	printf("************ 1 �߼����ʽ���б�               **********\n");
	printf("************ 2 �߼����ʽ����ֵ(�����û�ȡֵ) **********\n");
	printf("��ѡ����Ҫ�Ĳ���:");
	scanf("%d",&choose);
	switch(choose)
	{
	    case 1:
		creattree(string, &T);
		for (i = 0; i < sum; i++)
		{
		    creatcombination(i, n);
		    result += value_tree(T);
		}
		if(result == 0)
		    printf("Expression:%s False Forever\n", string);
		if(sum == result)
		    printf("Expression:%s True Forever\n", string);
		if(result > 0 && result < sum)
		    printf("Expression:%s Satisfatible\n", string);
		break;
	    case 2:
		creattree(string, &T);
		user(n);
		printf("�߼����ʽ��ֵΪ��%d\n", value_tree(T));
		break;
	}

	printf("�Ƿ�����������㣿�ǰ�1/ ��0:");
	scanf("%d", &choice);
	if(choice == 0)
	    exit(0);
    }
    return 0;


}
