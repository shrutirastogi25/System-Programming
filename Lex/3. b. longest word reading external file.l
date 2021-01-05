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
	yyin=fopen("file3","r");
	yylex();
	printf("\nLongest word is: \"%s\" with %d characters.\n", word,longest);
	return 0;
}
