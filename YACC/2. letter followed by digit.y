%{
#include<stdio.h>
#include<stdlib.h>
%}

%token DIGIT LETTER NL

%%
stmt: P {printf("VALID STRING\n");
	   exit(0);
	}
     ;
P: LETTER S DIGIT NL 
| LETTER DIGIT NL
;
S: S DIGIT
| S LETTER
| LETTER 
| DIGIT
;
%%

int yyerror(){
	printf("INVALID STRING\n");
	return 1;
}

int main(){
	printf("Enter String\n");
	yyparse();
	return 1;
}


