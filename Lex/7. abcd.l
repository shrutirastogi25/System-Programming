%option noyywrap
%option main

%%
a |
ab |
abc |
abcd ECHO; printf("\n"); REJECT;
.|\n ;
%%
