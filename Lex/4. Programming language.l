%option noyywrap
digit [0-9]
letter [A-Za-z_]
star [*]
slash [/]

%%
" "|"\t"|"("|")" ;
int|main {for(int i=0;i<yyleng;i++)
		{
		printf("%c",yytext[i]);
		}
	   printf(":\t Keyword\n");
	 }
{digit}+ {for(int i=0;i<yyleng;i++)
		{
		printf("%c",yytext[i]);
		}
	   printf(":\t Integer\n");
	  }
{digit}+.{digit}+ {for(int i=0;i<yyleng;i++)
			{
			printf("%c",yytext[i]);
			}
	   		printf(":\t Float\n");
		   }

"+" |
"-" |
"*" |
"/" |
"=" {for(int i=0;i<yyleng;i++)
	{
	printf("%c",yytext[i]);
	}
	printf(":\t Operator\n");
     }
{letter}({letter}|{digit})* {for(int i=0;i<yyleng;i++)
				{
				printf("%c",yytext[i]);
				}
	   			printf(":\t identifier\n");
           		     } 
{slash}{star}{letter}*{star}{slash} {for(int i=0;i<yyleng;i++)
					{
					printf("%c",yytext[i]);
					}
	   				printf(":\t Comment\n");
				     }

%%

int main(int argc,char*argv[])
{
if(argc<2){
	printf("Enter the file name\n");
	return 0;
}
yyin=fopen(argv[1],"r");
yylex();
}

