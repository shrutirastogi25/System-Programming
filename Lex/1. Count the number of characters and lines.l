%option noyywrap
%{
int charcount=0, linecount=0;
%}

%%
. charcount++;
\n {linecount++; charcount++;}
%%

int main(){
	yyin=fopen("file1","r");
	yylex();
	printf("Character count %d line count %d \n", charcount,linecount);
}
