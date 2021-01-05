%option noyywrap

%{
	#include<string.h>
	int longest=0;
	char word[60];
%}

%%
[a-zA-Z]+ {
	if(yyleng > longest){
		longest=yyleng;
		strcpy(word,yytext);
	}
}
. |
\n ;
%%

int main(){
	yylex();
	printf("\nLongest word is: \"%s\" with %d characters.\n", word,longest);
	return 0;
}
