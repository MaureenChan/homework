%{
#include <stdio.h>
%}

%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL

%%

calclist:
		| calclist exp EOL { printf("= %d\n", $2); }
		;

exp:factor default $$ = $1
   | exp ADD factor { $$ = $1 + $3; }
   | exp SUB factor { $$ = $1 - $3; }
   ;

factor: term default $$ = $1
	  | factor MUL term { $$ ＝$1 * $3; }
	  | factor DIV term { $$ ＝$1 / $3; }
	  ;

