%option noyywrap
digit [0-9]
letter [A-Za-z_]
star [*]
slash [/]
%{
int count=0;
%}

%%
" "|"\t"|"("|")"|;|"{"|"}"|"\n" ;
int|main {;
	 }
{digit}+ {;
	  }
{digit}+.{digit}+ {;
		}

"+" |
"-" |
"*" |
"/" |
"=" {;
     }
{letter}({letter}|{digit})* {count++;
           		     } 
{slash}{star}{letter}*{star}{slash} {;
				     }

%%

int main(int argc, char* argv[])
{
if(argc<2){
	printf("ERROR. Enter file name\n");
	return 0;
}
yyin=fopen("file4","r");
yylex();
printf("No. of identifiers in the file is \"%d\"\n",count);
}

