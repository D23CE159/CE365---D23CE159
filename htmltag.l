%{

#include <stdio.h>

%}

%option noyywrap

%%

"<"(html|head|title|body|div|span)">"	{ printf("Valid HTML Tag: %s\n", yytext); }

"</"(html|head|title|body|div|span)">"	{ printf("Valid Closing HTML tag: %s\n", yytext); }

"<"{2,}[^<>]+">"{2,}	{printf("Invalid HTML Tag: %s\n", yytext);}
"<"[^<>]+">"	{ printf("Invalid HTML Tag: %s\n", yytext); }

.	{}

%%

int main() {
	printf("Enter an HTML tag: ");
	yylex();
	return 0;
}