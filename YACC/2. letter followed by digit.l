%{
#include"y.tab.h"
%}

%%
[0-9] {return DIGIT;}
[a-z] {return LETTER;}
\n {return NL;}
. {return yytext[0];}
%%

int yywrap(){
	return 1;
}
