%{
	#include<stdio.h>
	#include<stdlib.h>
%}

%token A B NL

%%
stmt: A S B  NL {
			printf("VALID STRING\n");
			exit(0);
		       }
;
S: S B
|
;
%%

int yyerror(char *msg){
	printf("INVALID STRING\n");
	exit(0);
}

int main(){
	printf("Enter the string\n");
	yyparse();
	return 1;
}
