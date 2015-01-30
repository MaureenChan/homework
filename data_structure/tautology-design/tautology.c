
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

//存放变量可能的其中一种组合
int combination[BIANLIANG_MAX];    
//初始化栈
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
    (*tree)->lchild = l;    //拼接左右孩子
    (*tree)->rchild = r;
    if(l&&r)	//遇到叶子结点给左右孩子置空
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
    SqStack variable;	//变量栈
    SqStack logic;	//运算符栈
    BiTree e;		//存放运算符栈栈顶结点
    BiTree logic_di;	//运算符栈栈顶
    BiTree variables;	//变量栈栈顶
    BiTree logics;	//push参数
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

		    create(&boot_tree,b,a); //连接子树
		    Push(&variable,boot_tree);	//把子树压栈
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
	return combination[T->data - 65];  //直接返回叶子结点的值
    else if(T->data < 65 || T->data > 90)
	switch(T->data)	//计算与或非的值
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
    //定义变量
    int sum;	//用来表示总共表示的组合数
    int i = 0;		//循环
    int result = 0;	//用来判断重言式类别
    int choose,choice;	//用来选择
    int n;		//用来表示变量个数
    char str[STR_MAX], string[STR_MAX], *pstr;	//存储字符串
    InitBiTree(&T);
    printf("EnterVariable NUMber:\n");
    scanf("%d", &n);
    sum = pow(2,n);	//计算总共的组合数
    //处理字符串
    printf("Enter Expression:\n");
    scanf("%s", str);
    pstr = str;
    for (; *pstr; pstr++)
	if(*pstr != ' ')    //删掉空格
	    string[i++] = *pstr;
    string[i] = '#';	//最后用来判断建树完毕
    string[i + 1] = '\0';
    
    while(1)
    {
	printf("************          请选择你要的操作        **********\n");
	printf("************ 1 逻辑表达式的判别               **********\n");
	printf("************ 2 逻辑表达式的求值(根据用户取值) **********\n");
	printf("请选择你要的操作:");
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
		printf("逻辑表达式的值为：%d\n", value_tree(T));
		break;
	}

	printf("是否继续进行运算？是按1/ 否按0:");
	scanf("%d", &choice);
	if(choice == 0)
	    exit(0);
    }
    return 0;


}
