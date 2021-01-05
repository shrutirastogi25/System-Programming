%option noyywrap
operator [+\-\/*]
operand [0-9a-zA-Z]+

%{
	int op1,op2;
	int openBracket=0;
	int closeBracket=0;
%}

%%
{operator} {op1++;
	    printf("%s is an operator \n", yytext);
	}

{operand} {op2++;
	   printf("%s is an operand\n",yytext);
	}
"{"|"("|"[" {openBracket++;}
"}"|")"|"]" {closeBracket++;}

\n {
	if(openBracket == closeBracket && op2 > op1)
		printf("VALID ARITHMETIC EXPRESSION \n");
	else
		printf("INVALID ARITHMETIC EXPRESSION \n");
	exit(0);
}
%%

int main(){
	printf("Enter the Arithmetic expression:");
	yylex();
	return 0;
}
