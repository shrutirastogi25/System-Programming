%option noyywrap

%{
	char ch;
%}

%%
[a-z] {
	char ch=yytext[0];
	ch+=3;
	if(ch>'z')
		ch-=('z'+1-'a');
	printf("%c",ch);
}
[A-Z] {
	char ch=yytext[0];
	ch+=3;
	if(ch>'z')
		ch-=('Z'+1-'A');
	printf("%c",ch);
}
%%

int main(){
	yyin=fopen("file2","r");
	yylex();
	printf("%c",ch);
}

