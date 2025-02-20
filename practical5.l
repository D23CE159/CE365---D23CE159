%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Regular expressions for various tokens
char *keywords = "(auto|break|case|char|const|continue|default|do|int|long|"
                 "register|return|short|signed|sizeof|static|struct|switch|"
                 "typedef|union|unsigned|void|volatile|while)";

char *operators = "(=|\\+|\\-|\\*|/|%|&&|\\|\\||==|!=|<|<=|>|>=|\\+\\+|--|"
                  "&|\\||\\^|~|<<|>>)";

char *punctuations = "(\\(|\\)|\\{|\\}|,|;|:|\\[|\\]|\\.)";

char *special_symbols = "(#|\"|\')";

// Regular expressions for identifiers, constants, strings, and comments
char *id_re = "[a-zA-Z_][a-zA-Z0-9_]*";
char *const_re = "[0-9]+(\\.[0-9]+)?"; // Integer and floating-point constants
char *string_re = "\".*\"";
char *single_comment_re = "//.*";
char *multi_comment_re = "/\\*[^*]*\\*+([^/*][^*]*\\*+)*/";
%}

%option noyywrap

%%

/* Keywords */
{keywords}  { printf("Keyword: %s\n", yytext); }

/* Identifiers */
[a-zA-Z_][a-zA-Z0-9_]*   { printf("Identifier: %s\n", yytext); }

/* Constants (Integers and Floats) */
{const_re}                 { printf("Constant: %s\n", yytext); }

/* Strings */
{string_re}               { printf("String: %s\n", yytext); }

/* Punctuation */
{punctuations}            { printf("Punctuation: %s\n", yytext); }

/* Operators */
{operators}               { printf("Operator: %s\n", yytext); }

/* Special Symbols */
{special_symbols}         { printf("Special Symbol: %s\n", yytext); }

/* Single-line Comment */
{single_comment_re}       { /* Ignore single-line comments */ }

/* Multi-line Comment */
{multi_comment_re}        { /* Ignore multi-line comments */ }

/* Whitespaces */
[ \t\r\n]+                { /* Ignore whitespaces */ }

/* Lexical Errors */
.                         { printf("Lexical Error: Unrecognized token '%s'\n", yytext); }

%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        perror("File opening failed");
        return 1;
    }

    yyin = source_file;
    yylex();  // Start lexical analysis

    fclose(source_file);
    return 0;
}
