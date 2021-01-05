%{
	#include<stdio.h>
	int characters=0,words=0,spaces=0,lines=0;
%}

word[^ \t\n,\.:]+
endofline [\n]
blank[ ]

%%
{word} {
	words++;
	characters=characters+yyleng;
       }
{endofline} {
		lines++;
	    }
{blank} {
	  spaces++;
	}
%%

int yywrap(){
	return 1;
}

void main(int argc,char*argv[]){
	if(argc!=2){
		printf("Usage: ./p6 filename \n");
		exit(0);
	}
	yyin=fopen(argv[1],"r");
	yylex();
	printf("number of spaces: %d \n",spaces);
	printf("number of characters: %d \n",characters);
	printf("number of words: %d \n",words);
	printf("number of lines: %d \n",lines);
}
	
