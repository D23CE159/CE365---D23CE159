%{
#include <stdio.h>
int c_count = 0;
int w_count = 0;
int l_count = 0;
%}
%option noyywrap
%%
\n { c_count++; l_count++; }
[ \t] { c_count++; }
[^ \t\n]+ { w_count++; c_count += yyleng; }
. { c_count++; }
%%
void main() {
	yylex();
	printf("Characters: %d\n", c_count);
	printf("Words: %d\n", w_count);
	printf("Lines: %d\n", l_count);
}