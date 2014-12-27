/*** PL0 COMPILER WITH CODE GENERATION ***/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
const  AL    =  10;  /* LENGTH OF IDENTIFIERS */
const  NORW  =  21;  /* # OF RESERVED WORDS */
const  TXMAX = 100;  /* LENGTH OF IDENTIFIER TABLE */
const  NMAX  =  14;  /* MAX NUMBER OF DEGITS IN NUMBERS */
const  AMAX  =2045;  /* MAXIMUM ADDRESS */
const  LEVMAX=   3;  /* MAX DEPTH OF BLOCK NESTING */
const  CXMAX = 200;  /* SIZE OF CODE ARRAY */

typedef enum  { NUL, IDENT, NUMBER, PLUS, MINUS, TIMES,
	            SLASH, ODDSYM, EQL, NEQ, LSS, LEQ, GTR, GEQ,
	            LPAREN, RPAREN, COMMA, SEMICOLON, PERIOD,
	            BECOMES, BEGINSYM, ENDSYM, IFSYM, THENSYM,
	            WHILESYM, WRITESYM, READSYM, DOSYM, CALLSYM,
	            CONSTSYM, VARSYM, PROCSYM, PROGSYM,
				ELSESYM, FORSYM, STEPSYM, UNTILSYM, RETURNSYM,
				TIMESBECOMES, SLASHBECOMES, ANDSYM, ORSYM, NOTSYM,
} SYMBOL;
char *SYMOUT[] = {"NUL", "IDENT", "NUMBER", "PLUS", "MINUS", "TIMES",
	    "SLASH", "ODDSYM", "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ",
	    "LPAREN", "RPAREN", "COMMA", "SEMICOLON", "PERIOD",
	    "BECOMES", "BEGINSYM", "ENDSYM", "IFSYM", "THENSYM",
	    "WHILESYM", "WRITESYM", "READSYM", "DOSYM", "CALLSYM",
	    "CONSTSYM", "VARSYM", "PROCSYM", "PROGSYM" , 
		"ELSESYM", "FORSYM", "STEPSYM", "UNTILSYM", "RETURNSYM",
		"TIMESBECOMES", "SLASHBECOMES", "ANDSYM", "ORSYM", "NOTSYM",
};
typedef  int *SYMSET; // SET OF SYMBOL;
typedef  char ALFA[11];
typedef  enum { CONSTANT, VARIABLE, PROCEDUR, CHAR, REAL} OBJECTS ;
typedef  enum { LIT, OPR, LOD, STO, CAL, INI, JMP, JPC } FCT;
typedef struct {
	 FCT F;     /*FUNCTION CODE*/
	 int L; 	/*0..LEVMAX  LEVEL*/
	 int A;     /*0..AMAX    DISPLACEMENT ADDR*/
} INSTRUCTION;
	  /* LIT O A -- LOAD CONSTANT A             */
	  /* OPR 0 A -- EXECUTE OPR A               */
	  /* LOD L A -- LOAD VARIABLE L,A           */
	  /* STO L A -- STORE VARIABLE L,A          */
	  /* CAL L A -- CALL PROCEDURE A AT LEVEL L */
	  /* INI 0 A -- INCREMET T-REGISTER BY A    */
	  /* JMP 0 A -- JUMP TO A                   */
	  /* JPC 0 A -- JUMP CONDITIONAL TO A       */
char   CH;  /*LAST CHAR READ*/
SYMBOL SYM; /*LAST SYMBOL READ*/
ALFA   ID;  /*LAST IDENTIFIER READ*/
int    NUM; /*LAST NUMBER READ*/
int    CC;  /*CHARACTER COUNT*/
int    LL;  /*LINE LENGTH*/
int    CX;  /*CODE ALLOCATION INDEX*/
char   LINE[81];
INSTRUCTION  CODE[CXMAX];
ALFA    KWORD[NORW+1];
SYMBOL  WSYM[NORW+1];
SYMBOL  SSYM['^'+1];
ALFA    MNEMONIC[9];
SYMSET  DECLBEGSYS, STATBEGSYS, FACBEGSYS;

struct {
  ALFA NAME;
  OBJECTS KIND;
  union {
    int VAL;   /*CONSTANT*/
    struct { int LEVEL,ADR,SIZE; } vp;  /*VARIABLE,PROCEDUR:*/
  };
} TABLE[TXMAX];

FILE *FIN,*FOUT;
int ERR;

void EXPRESSION(SYMSET FSYS, int LEV, int &TX);
void TERM(SYMSET FSYS, int LEV, int &TX);
//---------------------------------------------------------------------------
int SymIn(SYMBOL SYM, SYMSET S1) {
  return S1[SYM];
}
//---------------------------------------------------------------------------
SYMSET SymSetUnion(SYMSET S1, SYMSET S2) {
  SYMSET S=(SYMSET)malloc(sizeof(int)*45);
  for (int i=0; i<45; i++)
	if (S1[i] || S2[i]) S[i]=1;
	else S[i]=0;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetAdd(SYMBOL SY, SYMSET S) {
  SYMSET S1;
  S1=(SYMSET)malloc(sizeof(int)*45);
  for (int i=0; i<45; i++) S1[i]=S[i];
  S1[SY]=1;
  return S1;
}
//---------------------------------------------------------------------------
SYMSET SymSetNew(SYMBOL a) {
  SYMSET S; int i,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  S[a]=1;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetNew(SYMBOL a, SYMBOL b) {
  SYMSET S; int i,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  S[a]=1;  S[b]=1;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetNew(SYMBOL a, SYMBOL b, SYMBOL c) {
  SYMSET S; int i,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  S[a]=1;  S[b]=1; S[c]=1;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetNew(SYMBOL a, SYMBOL b, SYMBOL c, SYMBOL d) {
  SYMSET S; int i,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  S[a]=1;  S[b]=1; S[c]=1; S[d]=1;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetNew(SYMBOL a, SYMBOL b, SYMBOL c, SYMBOL d,SYMBOL e) {
  SYMSET S; int i,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  S[a]=1;  S[b]=1; S[c]=1; S[d]=1; S[e]=1;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetNew(SYMBOL a, SYMBOL b, SYMBOL c, SYMBOL d,SYMBOL e, SYMBOL f) {
  SYMSET S; int i,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  S[a]=1;  S[b]=1; S[c]=1; S[d]=1; S[e]=1; S[f]=1;
  return S;
}
//---------------------------------------------------------------------------
SYMSET SymSetNULL() {
  SYMSET S; int i,n,k;
  S=(SYMSET)malloc(sizeof(int)*45);
  for (i=0; i<45; i++) S[i]=0;
  return S;
}
//---------------------------------------------------------------------------
void Error(int n) {
  String s = "***"+AnsiString::StringOfChar(' ', CC-1)+"^";
  Form1->printls(s.c_str(),n);   fprintf(FOUT,"%s%d\n", s.c_str(), n);
  ERR++;
} /*Error*/
//---------------------------------------------------------------------------
void GetCh() {
  if (CC==LL) {
    if (feof(FIN)) {
	  Form1->printfs("PROGRAM INCOMPLETE");
	  fprintf(FOUT,"PROGRAM INCOMPLETE\n");
	  fclose(FOUT);
	  exit(0);
	}
	LL=0; CC=0;
	CH=' ';
	while (!feof(FIN) && CH!=10)
      { CH=fgetc(FIN);  LINE[LL++]=CH; }
	LINE[LL-1]=' ';  LINE[LL]=0;
    String s=IntToStr(CX);
    while(s.Length()<3) s=" "+s;
    s=s+" "+LINE;
	Form1->printfs(s.c_str());
    fprintf(FOUT,"%s\n",s);
  }
  CH=LINE[CC++];
} /*GetCh()*/
//---------------------------------------------------------------------------
void GetSym() {
  int i,J,K;   ALFA  A;
  while (CH<=' ') GetCh();
  if (CH>='A' && CH<='Z') { /*ID OR RESERVED WORD*/
    K=0;
	do {
	  if (K<AL) A[K++]=CH;
	  GetCh();
	}while((CH>='A' && CH<='Z')||(CH>='0' && CH<='9'));
	A[K]='\0';
	strcpy(ID,A); i=1; J=NORW;
	do {
	  K=(i+J) / 2;
	  if (strcmp(ID,KWORD[K])<=0) J=K-1;
	  if (strcmp(ID,KWORD[K])>=0) i=K+1;
	}while(i<=J);
	if (i-1 > J) SYM=WSYM[K];
	else SYM=IDENT;
  }
  else
    if (CH>='0' && CH<='9') { /*NUMBER*/
      K=0; NUM=0; SYM=NUMBER;
	  do {
	    NUM=10*NUM+(CH-'0');
		K++; GetCh();
      }while(CH>='0' && CH<='9');
	  if (K>NMAX) Error(30);
    }
    else
      if (CH==':') {
	    GetCh();
		if (CH=='=') { SYM=BECOMES; GetCh(); }
		else SYM=NUL;
      }
	  else /* THE FOLLOWING TWO CHECK WERE ADDED
	         BECAUSE ASCII DOES NOT HAVE A SINGLE CHARACTER FOR <= OR >= */
	    if (CH=='<') {
		  GetCh();
		  if (CH=='=') { SYM=LEQ; GetCh(); }
			if (CH=='>') {SYM=NEQ; GetCh();}
			  else SYM=LSS;
		}
		else
		  if (CH=='>') {
		    GetCh();
			if (CH=='=') { SYM=GEQ; GetCh(); }
			else SYM=GTR;
          }
		  else
			if (CH=='*') {
				GetCh();
				if(CH=='='){SYM=TIMESBECOMES; GetCh();}
				else SYM=TIMES;
			}
			else
				if(CH=='/') {	
					GetCh();		//如果遇到'/',配对，获取下一个字符
					if(CH=='='){	//如果下一个字符是等号的话
						SYM=SLASHBECOMES; //类型就为SLASHBECOMES, 即为'/='
						GetCh();	//获取下一个字符
					}
					else if(CH=='*'){	//如果下一个字符是'*',那么就识别到'/*'
						while(1){		
							GetCh();	//不断获取字符
							if(CH=='*'){	//如果获取的字符是'*'
								GetCh();	//再获取下一个字符
								if(CH=='/')	//如果是'/',则识别到'*/'
									break;	//注释结束，跳出循环
							}
						}
						GetCh();
						GetSym();
					}
					else SYM=SLASH;	//如果都不是的话，则识别为'/'
				}
				else 
					if(CH=='&'){
						SYM=ANDSYM;
						GetCh();
					}
					else
						if(CH=='|'){
							GetCh();
							if(CH=='|'){
								SYM=ORSYM;
								GetCh();
							}
							else Error(19);
						}
						else
							if(CH=='!'){
								SYM=NOTSYM;
								GetCh();
							}
		  else { SYM=SSYM[CH]; GetCh(); }
} /*GetSym()*/
//---------------------------------------------------------------------------
void GEN(FCT X, int Y, int Z) {
  if (CX>CXMAX) {
    Form1->printfs("PROGRAM TOO LONG");
	fprintf(FOUT,"PROGRAM TOO LONG\n");
	fclose(FOUT);
    exit(0);
  }
  CODE[CX].F=X; CODE[CX].L=Y; CODE[CX].A=Z;
  CX++;
} /*GEN*/
//---------------------------------------------------------------------------
void TEST(SYMSET S1, SYMSET S2, int N) {
  if (!SymIn(SYM,S1)) {
    Error(N);
	while (!SymIn(SYM,SymSetUnion(S1,S2))) GetSym();
  }
} /*TEST*/
//---------------------------------------------------------------------------
void ENTER(OBJECTS K, int LEV, int &TX, int &DX) { /*ENTER OBJECT INTO TABLE*/
  TX++;
  strcpy(TABLE[TX].NAME,ID); TABLE[TX].KIND=K;
  switch (K) {
	case CONSTANT:
	       if (NUM>AMAX) { Error(31); NUM=0; }
	       TABLE[TX].VAL=NUM;
	       break;
    case VARIABLE:
	       TABLE[TX].vp.LEVEL=LEV; TABLE[TX].vp.ADR=DX; DX++;
	       break;
	case PROCEDUR:
	       TABLE[TX].vp.LEVEL=LEV;
	       break;
  }
} /*ENTER*/
//---------------------------------------------------------------------------
int POSITION(ALFA ID, int TX) { /*FIND IDENTIFIER IN TABLE*/
  int i=TX;
  strcpy(TABLE[0].NAME,ID);
  while (strcmp(TABLE[i].NAME,ID)!=0) i--;
  return i;
} /*POSITION*/
//---------------------------------------------------------------------------
void ConstDeclaration(int LEV,int &TX,int &DX) {
  if (SYM==IDENT) {
    GetSym();
    if (SYM==EQL||SYM==BECOMES) {
	  if (SYM==BECOMES) Error(1);
	  GetSym();
	  if (SYM==NUMBER) { ENTER(CONSTANT,LEV,TX,DX); GetSym(); }
	  else Error(2);
    }
    else Error(3);
  }
  else Error(4);
} /*ConstDeclaration()*/
//---------------------------------------------------------------------------
void VarDeclaration(int LEV,int &TX,int &DX) {
  if (SYM==IDENT) { ENTER(VARIABLE,LEV,TX,DX); GetSym(); }
  else Error(4);
} /*VarDeclaration()*/
//---------------------------------------------------------------------------
void ListCode(int CX0) {  /*LIST CODE GENERATED FOR THIS Block*/
  if (Form1->ListSwitch->ItemIndex==0)
    for (int i=CX0; i<CX; i++) {
      String s=IntToStr(i);
      while(s.Length()<3)s=" "+s;
      s=s+" "+MNEMONIC[CODE[i].F]+" "+IntToStr(CODE[i].L)+" "+IntToStr(CODE[i].A);
	  Form1->printfs(s.c_str());
	  fprintf(FOUT,"%3d%5s%4d%4d\n",i,MNEMONIC[CODE[i].F],CODE[i].L,CODE[i].A);
    }
} /*ListCode()*/;
//---------------------------------------------------------------------------
void FACTOR(SYMSET FSYS, int LEV, int &TX) {
  int i;
  TEST(FACBEGSYS,FSYS,24);
  while (SymIn(SYM,FACBEGSYS)) {
	if (SYM==IDENT) {
	  i=POSITION(ID,TX);
	  if (i==0) Error(11);
	  else
		switch (TABLE[i].KIND) {
		  case CONSTANT: GEN(LIT,0,TABLE[i].VAL); break;
		  case VARIABLE: GEN(LOD,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR); break;
		  case PROCEDUR: Error(21); break;
		}
	  GetSym();
	}
	else
	  if (SYM==NUMBER) {
		if (NUM>AMAX) { Error(31); NUM=0; }
		GEN(LIT,0,NUM); GetSym();
	  }
	  else
		if (SYM==LPAREN) {
		  GetSym(); EXPRESSION(SymSetAdd(RPAREN,FSYS),LEV,TX);
		  if (SYM==RPAREN) GetSym();
		  else Error(22);
		}
	  TEST(FSYS,FACBEGSYS,23);
  }
}/*FACTOR*/
//---------------------------------------------------------------------------
void TERM(SYMSET FSYS, int LEV, int &TX) {  /*TERM*/
  SYMBOL MULOP;
  FACTOR(SymSetUnion(FSYS,SymSetNew(TIMES,SLASH)), LEV,TX);
  while (SYM==TIMES || SYM==SLASH) {
	MULOP=SYM;  GetSym();
	FACTOR(SymSetUnion(FSYS,SymSetNew(TIMES,SLASH)),LEV,TX);
	if (MULOP==TIMES) GEN(OPR,0,4);
	else GEN(OPR,0,5);
  }
} /*TERM*/;
//---------------------------------------------------------------------------
void EXPRESSION(SYMSET FSYS, int LEV, int &TX) {
  SYMBOL ADDOP;
  if (SYM==PLUS || SYM==MINUS) {
    ADDOP=SYM; GetSym();
    TERM(SymSetUnion(FSYS,SymSetNew(PLUS,MINUS)),LEV,TX);
    if (ADDOP==MINUS) GEN(OPR,0,1);
  }
  else TERM(SymSetUnion(FSYS,SymSetNew(PLUS,MINUS)),LEV,TX);
  while (SYM==PLUS || SYM==MINUS) {
    ADDOP=SYM; GetSym();
    TERM(SymSetUnion(FSYS,SymSetNew(PLUS,MINUS)),LEV,TX);
    if (ADDOP==PLUS) GEN(OPR,0,2);
    else GEN(OPR,0,3);
  }
} /*EXPRESSION*/
//---------------------------------------------------------------------------
void CONDITION(SYMSET FSYS,int LEV,int &TX) {
  SYMBOL RELOP;
  if (SYM==ODDSYM) { GetSym(); EXPRESSION(FSYS,LEV,TX); GEN(OPR,0,6); }
  else {
	EXPRESSION(SymSetUnion(SymSetNew(EQL,NEQ,LSS,LEQ,GTR,GEQ),FSYS),LEV,TX);
	if (!SymIn(SYM,SymSetNew(EQL,NEQ,LSS,LEQ,GTR,GEQ))) Error(20);
	else {
	  RELOP=SYM; GetSym(); EXPRESSION(FSYS,LEV,TX);
	  switch (RELOP) {
	    case EQL: GEN(OPR,0,8);  break;
	    case NEQ: GEN(OPR,0,9);  break;
	    case LSS: GEN(OPR,0,10); break;
	    case GEQ: GEN(OPR,0,11); break;
	    case GTR: GEN(OPR,0,12); break;
	    case LEQ: GEN(OPR,0,13); break;
	  }
	}
  }
} /*CONDITION*/
//---------------------------------------------------------------------------
void STATEMENT(SYMSET FSYS,int LEV,int &TX) {   /*STATEMENT*/
  int i,CX1,CX2;
  switch (SYM) {
	case IDENT:
		i=POSITION(ID,TX);
		if (i==0) Error(11);
		else
		  if (TABLE[i].KIND!=VARIABLE) { /*ASSIGNMENT TO NON-VARIABLE*/
			Error(12); i=0;
		  }
        GetSym();

		if (SYM==BECOMES) {
			GetSym();
			EXPRESSION(FSYS,LEV,TX);
		}
		//如果为'*='
		//则计算*=右边表达式的值，并放到栈顶
		//把*=左边的标识符的值放到栈顶
		//栈顶和次栈顶相乘
		else if(SYM==TIMESBECOMES){		
			GetSym();
			EXPRESSION(FSYS,LEV,TX);
			GEN(LOD,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
			GEN(OPR,0, 4);
		}
		//如果为'/='
		//计算/=右边表达式的值，并放到栈顶
		//把/=左边标识符的值放到栈顶
		//栈顶和次栈顶相除
		else if(SYM==SLASHBECOMES){
			GetSym();
			GEN(LOD,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
			EXPRESSION(FSYS,LEV,TX);
			GEN(OPR, 0, 5);
		}
		else Error(13);

		//最后把结果存储到变量中
		GEN(STO,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
		break;
	case READSYM:
		GetSym();
		if (SYM!=LPAREN) Error(34);
		else
		  do {
			GetSym();
			if (SYM==IDENT) i=POSITION(ID,TX);
			else i=0;
			if (i==0) Error(35);
			else {
			  GEN(OPR,0,16);
			  GEN(STO,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
			}
			GetSym();
		  }while(SYM==COMMA);
		if (SYM!=RPAREN) {
		  Error(45);
		  while (!SymIn(SYM,FSYS)) GetSym();
		}
		else GetSym();
		break; /* READSYM */
	case WRITESYM:
		GetSym();
		if (SYM==LPAREN) {
		  do {
			GetSym();
			EXPRESSION(SymSetUnion(SymSetNew(RPAREN,COMMA),FSYS),LEV,TX);
			GEN(OPR,0,14);
		  }while(SYM==COMMA);
		  if (SYM!=RPAREN) Error(45);
		  else GetSym();
		}
		GEN(OPR,0,15);
		break; /*WRITESYM*/
	case CALLSYM:
		GetSym();
		if (SYM!=IDENT) Error(14);
		else {
		  i=POSITION(ID,TX);
		  if (i==0) Error(11);
		  else
			if (TABLE[i].KIND==PROCEDUR)
			  GEN(CAL,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
			else Error(15);
		  GetSym();
		}
		break;
	case IFSYM:
		GetSym();
		CONDITION(SymSetUnion(SymSetNew(THENSYM,DOSYM),FSYS),LEV,TX);
		if (SYM==THENSYM) GetSym();
		else Error(16);
		CX1=CX;  GEN(JPC,0,0);
		STATEMENT(FSYS,LEV,TX);  

		if(SYM==SEMICOLON){
			GetSym();
		}
		CX2=CX;
		GEN(JMP,0,0);
		CODE[CX1].A=CX;
		if (SYM==ELSESYM) {
			GetSym();
			STATEMENT(FSYS,LEV,TX);  
		}
		CODE[CX2].A=CX;
		break;
	case BEGINSYM:
		GetSym();
		STATEMENT(SymSetUnion(SymSetNew(SEMICOLON,ENDSYM),FSYS),LEV,TX);
		while (SymIn(SYM, SymSetAdd(SEMICOLON,STATBEGSYS))) {
		  if (SYM==SEMICOLON) GetSym();
		  else Error(10);
		  STATEMENT(SymSetUnion(SymSetNew(SEMICOLON,ENDSYM),FSYS),LEV,TX);
		}
		if (SYM==ENDSYM) GetSym();
		else Error(17);
		break;
	case WHILESYM:
		CX1=CX; GetSym(); CONDITION(SymSetAdd(DOSYM,FSYS),LEV,TX);
		CX2=CX; GEN(JPC,0,0);
		if (SYM==DOSYM) GetSym();
		else Error(18);
		STATEMENT(FSYS,LEV,TX);
		GEN(JMP,0,CX1);
		CODE[CX2].A=CX;
		break;
	case FORSYM:
		//VARIABLE
		GetSym();
		if(SYM==IDENT){			//判断是不是一个标识符
			i=POSITION(ID,TX);	//是的话就查表,把标识符的序号返回到i中
			if (i==0)			//如果表中没有定义，则出错
				Error(11);
			else
			  if (TABLE[i].KIND!=VARIABLE) { /*ASSIGNMENT TO NON-VARIABLE*/
				Error(12);		//如果不是变量，则出错
				i=0;
			  }

			//BECOMES
			GetSym();
			if (SYM==BECOMES) {	//匹配等号
				GetSym();
			}
			else 
				Error(13);

			//EXPRESSION
			EXPRESSION(SymSetUnion(SymSetNew(STEPSYM),FSYS),LEV,TX);	//匹配表达式,此时表达式的值在栈顶
			if (i!=0) 
				GEN(STO,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);	//把栈顶的值存储到标识符中


			//匹配STEP
			if(SYM==STEPSYM){
				//EXPRESSION
				GetSym();
				//保存(JMP,0,0)这条指令在CODE中的地址CX1
				//因为编译时还不知道要跳转到的地址
				//CX2地址为执行完语句体后跳转到此处
				//所以需要记录CX2的地址
				CX1=CX;	
				GEN(JMP,0,0);
				CX2=CX;

				//把栈顶的变量的值放到栈顶
				GEN(LOD,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
				//就是STEP后的表达式的值并放到栈顶
				EXPRESSION(SymSetUnion(SymSetNew(UNTILSYM),FSYS),LEV,TX);
				//将次栈顶和栈顶的两个值相加(变量与步长相加)
				GEN(OPR,0,2);
				if (i!=0) 
					//相加结果在栈顶，把结果保存到变量中
					GEN(STO,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);

				//UNTIL
				if(SYM==UNTILSYM){
					GetSym();
					//回填(JMP,0,0)中的目标地址域
					//因为给变量赋初值后要跳到判断是否符合循环条件
					CODE[CX1].A=CX;

					//把变量的值提到栈顶
					//计算表达式的值,并放在栈顶
					//把次栈顶和栈顶作比较
					//成功了则继续执行
					//不成功则跳到For语句结束处
					GEN(LOD,LEV-TABLE[i].vp.LEVEL,TABLE[i].vp.ADR);
					EXPRESSION(SymSetUnion(SymSetNew(DOSYM),FSYS),LEV,TX);
					GEN(OPR,0,13);
					CX1=CX;
					GEN(JPC,0,0);

					//执行语句
					//执行完后跳转到步长处
					if(SYM==DOSYM){
						GetSym();
						STATEMENT(SymSetUnion(SymSetNew(SEMICOLON),FSYS),LEV,TX);
						GEN(JMP,0,CX2);
					} else Error(8);
				} else Error(8);
			}else Error(8);
		}else Error(8);

		//For结束
		CODE[CX1].A=CX;
  }
  TEST(FSYS,SymSetNULL(),19);
} /*STATEMENT*/
//---------------------------------------------------------------------------
void Block(int LEV, int TX, SYMSET FSYS) {
  int DX=3;    /*DATA ALLOCATION INDEX*/
  int TX0=TX;  /*INITIAL TABLE INDEX*/
  int CX0=CX;  /*INITIAL CODE INDEX*/
  TABLE[TX].vp.ADR=CX; GEN(JMP,0,0);
  if (LEV>LEVMAX) Error(32);
  do {
    if (SYM==CONSTSYM) {
      GetSym();
      do {
        ConstDeclaration(LEV,TX,DX);
        while (SYM==COMMA) {
          GetSym();  ConstDeclaration(LEV,TX,DX);
        }
        if (SYM==SEMICOLON) GetSym();
        else Error(5);
      }while(SYM==IDENT);
    }
    if (SYM==VARSYM) {
      GetSym();
      do {
        VarDeclaration(LEV,TX,DX);
        while (SYM==COMMA) { GetSym(); VarDeclaration(LEV,TX,DX); }
	    if (SYM==SEMICOLON) GetSym();
	    else Error(5);
      }while(SYM==IDENT);
    }
    while ( SYM==PROCSYM) {
      GetSym();
	  if (SYM==IDENT) { ENTER(PROCEDUR,LEV,TX,DX); GetSym(); }
	  else Error(4);
	  if (SYM==SEMICOLON) GetSym();
	  else Error(5);
	  Block(LEV+1,TX,SymSetAdd(SEMICOLON,FSYS));
	  if (SYM==SEMICOLON) {
	    GetSym();
	    TEST(SymSetUnion(SymSetNew(IDENT,PROCSYM),STATBEGSYS),FSYS,6);
	  }
	  else Error(5);
    }
    TEST(SymSetAdd(IDENT,STATBEGSYS), DECLBEGSYS,7);
  }while(SymIn(SYM,DECLBEGSYS));
  CODE[TABLE[TX0].vp.ADR].A=CX;
  TABLE[TX0].vp.ADR=CX;   /*START ADDR OF CODE*/
  TABLE[TX0].vp.SIZE=DX;  /*SIZE OF DATA SEGMENT*/
  GEN(INI,0,DX);
  STATEMENT(SymSetUnion(SymSetNew(SEMICOLON,ENDSYM),FSYS),LEV,TX);
  GEN(OPR,0,0);  /*RETURN*/
  TEST(FSYS,SymSetNULL(),8);
  ListCode(CX0);
} /*Block*/
//---------------------------------------------------------------------------
int BASE(int L,int B,int S[]) {
  int B1=B; /*FIND BASE L LEVELS DOWN*/
  while (L>0) { B1=S[B1]; L=L-1; }
  return B1;
} /*BASE*/
//---------------------------------------------------------------------------
void Interpret() {
  const STACKSIZE = 500;
  int P,B,T; 		/*PROGRAM BASE TOPSTACK REGISTERS*/
  INSTRUCTION I;
  int S[STACKSIZE];  	/*DATASTORE*/
  Form1->printfs("~~~ RUN PL0 ~~~");
  fprintf(FOUT,"~~~ RUN PL0 ~~~\n");
  T=0; B=1; P=0;
  S[1]=0; S[2]=0; S[3]=0;
  do {
    I=CODE[P]; P=P+1;
    switch (I.F) {
      case LIT: T++; S[T]=I.A; break;
	  case OPR:
	    switch (I.A) { /*OPERATOR*/
	      case 0: /*RETURN*/ T=B-1; P=S[T+3]; B=S[T+2]; break;
	      case 1: S[T]=-S[T];  break;
	      case 2: T--; S[T]=S[T]+S[T+1];   break;
	      case 3: T--; S[T]=S[T]-S[T+1];   break;
	      case 4: T--; S[T]=S[T]*S[T+1];   break;
	      case 5: T--; S[T]=S[T]/S[T+1]; break;		//除法操作
	      case 6: S[T]=(S[T]%2!=0);        break;
	      case 8: T--; S[T]=S[T]==S[T+1];  break;
	      case 9: T--; S[T]=S[T]!=S[T+1];  break;
	      case 10: T--; S[T]=S[T]<S[T+1];   break;
	      case 11: T--; S[T]=S[T]>=S[T+1];  break;
	      case 12: T--; S[T]=S[T]>S[T+1];   break;
	      case 13: T--; S[T]=S[T]<=S[T+1];  break;
	      case 14: Form1->printls("",S[T]); fprintf(FOUT,"%d\n",S[T]); T--;
                   break;
	      case 15: /*Form1->printfs(""); fprintf(FOUT,"\n"); */ break;
	      case 16: T++;  S[T]=InputBox("输入","请键盘输入：", 0).ToInt();
                   Form1->printls("? ",S[T]); fprintf(FOUT,"? %d\n",S[T]);
		           break;
	    }
	    break;
      case LOD: T++; S[T]=S[BASE(I.L,B,S)+I.A]; break;
      case STO: S[BASE(I.L,B,S)+I.A]=S[T]; T--; break;
	  case CAL: /*GENERAT NEW Block MARK*/
	      S[T+1]=BASE(I.L,B,S); S[T+2]=B; S[T+3]=P;
	      B=T+1; P=I.A; break;
	  case INI: T=T+I.A;  break;
	  case JMP: P=I.A; break;
      case JPC: if (S[T]==0) P=I.A;  T--;  break;
    } /*switch*/
  }while(P!=0);
  Form1->printfs("~~~ END PL0 ~~~");
  fprintf(FOUT,"~~~ END PL0 ~~~\n");
} /*Interpret*/
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonRunClick(TObject *Sender) {
  for (CH=' '; CH<='^'; CH++) SSYM[CH]=NUL;
  strcpy(KWORD[ 1],"BEGIN");    
  strcpy(KWORD[ 2],"CALL");
  strcpy(KWORD[ 3],"CHAR");
  strcpy(KWORD[ 4],"CONST");    
  strcpy(KWORD[ 5],"DO");
  strcpy(KWORD[ 6],"ELSE");		
  strcpy(KWORD[ 7],"END");      
  strcpy(KWORD[ 8],"FOR");		
  strcpy(KWORD[ 9],"IF");
  strcpy(KWORD[10],"ODD");      
  strcpy(KWORD[11],"PROCEDURE");
  strcpy(KWORD[12],"PROGRAM");  
  strcpy(KWORD[13],"READ");
  strcpy(KWORD[14],"REAL");
  strcpy(KWORD[15],"RETURN");	
  strcpy(KWORD[16],"STEP");
  strcpy(KWORD[17],"THEN");     
  strcpy(KWORD[18],"UNTIL");
  strcpy(KWORD[19],"VAR");		
  strcpy(KWORD[20],"WHILE");    
  strcpy(KWORD[21],"WRITE");
  WSYM[ 1]=BEGINSYM;   
  WSYM[ 2]=CALLSYM;
  WSYM[ 3]=CHARSYM;
  WSYM[ 4]=CONSTSYM;   
  WSYM[ 5]=DOSYM;
  WSYM[ 6]=ELSESYM;    
  WSYM[ 7]=ENDSYM;			
  WSYM[ 8]=FORSYM;	   
  WSYM[ 9]=IFSYM;
  WSYM[10]=ODDSYM;     
  WSYM[11]=PROCSYM;
  WSYM[12]=PROGSYM;    
  WSYM[13]=READSYM;
  WSYM[14]=REALSYM;
  WSYM[15]=RETURNSYM;  
  WSYM[16]=STEPSYM;
  WSYM[17]=THENSYM;    
  WSYM[18]=UNTILSYM;
  WSYM[19]=VARSYM;	   
  WSYM[20]=WHILESYM;   
  WSYM[21]=WRITESYM;
  SSYM['+']=PLUS;      SSYM['-']=MINUS;
  SSYM['*']=TIMES;     SSYM['/']=SLASH;
  SSYM['(']=LPAREN;    SSYM[')']=RPAREN;
  SSYM['=']=EQL;       SSYM[',']=COMMA;
  SSYM['.']=PERIOD;    SSYM['&']=ANDSYM;
  SSYM[';']=SEMICOLON; SSYM['!']=NOTSYM;
  strcpy(MNEMONIC[LIT],"LIT");   strcpy(MNEMONIC[OPR],"OPR");
  strcpy(MNEMONIC[LOD],"LOD");   strcpy(MNEMONIC[STO],"STO");
  strcpy(MNEMONIC[CAL],"CAL");   strcpy(MNEMONIC[INI],"INI");
  strcpy(MNEMONIC[JMP],"JMP");   strcpy(MNEMONIC[JPC],"JPC");

  DECLBEGSYS=(int*)malloc(sizeof(int)*45);
  STATBEGSYS=(int*)malloc(sizeof(int)*45);
  FACBEGSYS =(int*)malloc(sizeof(int)*45);
  for(int j=0; j<45; j++) {
	DECLBEGSYS[j]=0;  STATBEGSYS[j]=0;  FACBEGSYS[j] =0;
  }
  DECLBEGSYS[CONSTSYM]=1;
  DECLBEGSYS[VARSYM]=1;
  DECLBEGSYS[PROCSYM]=1;
  DECLBEGSYS[CHARSYM]=1;
  DECLBEGSYS[REAL]=1;
  STATBEGSYS[BEGINSYM]=1;
  STATBEGSYS[CALLSYM]=1;
  STATBEGSYS[IFSYM]=1;
  STATBEGSYS[WHILESYM]=1;
  STATBEGSYS[WRITESYM]=1;
  STATBEGSYS[FORSYM]=1;	//开始符号集中添加forsym
  FACBEGSYS[IDENT] =1;
  FACBEGSYS[NUMBER]=1;
  FACBEGSYS[LPAREN]=1;

  if ((FIN=fopen((Form1->EditName->Text+".PL0").c_str(),"r"))!=0) {
	FOUT=fopen((Form1->EditName->Text+".COD").c_str(),"w");
    Form1->printfs("=== COMPILE PL0 ===");
    fprintf(FOUT,"=== COMPILE PL0 ===\n");
	ERR=0;
	CC=0; CX=0; LL=0; CH=' '; GetSym();
	if (SYM!=PROGSYM) Error(0);
	else {
	  GetSym();
	  if (SYM!=IDENT) Error(0);
	  else {
		GetSym();
		if (SYM!=SEMICOLON) Error(5);
		else GetSym();
	  }
	}
	Block(0,0,SymSetAdd(PERIOD,SymSetUnion(DECLBEGSYS,STATBEGSYS)));
	if (SYM!=PERIOD) Error(9);
	if (ERR==0) Interpret();
	else {
	  Form1->printfs("ERROR IN PL/0 PROGRAM");
	  fprintf(FOUT,"ERROR IN PL/0 PROGRAM");
	}
	fprintf(FOUT,"\n"); fclose(FOUT);
  }
}
//---------------------------------------------------------------------------

