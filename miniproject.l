%{
#include <stdio.h>
#include <string.h>

int is_valid = 0;
int indent = 0;
int flag = 0;
%}

%option noyywrap

%%

^for[ \t]+[a-zA-Z_][a-zA-Z0-9_]*[ \t]*in[ \t]*.+:[ \t]*$ {
    is_valid = 1;
    indent = 1;
}

^[ ]{4}[^ ].* {
    if (indent) {
        indent = 1;
    }
}

^[ ]{0,3}[^ \n].*|^[ ]{5,}.* {
    if (indent) {  
        flag = 1;
    }
}

.|\n {
    if (!is_valid && !flag) {
        flag = 1;
    }
}

%%

int main() {
    printf("Enter a Python for loop statement (multi-line allowed, press Ctrl+D to submit):\n");
    yylex();

    if (is_valid && !flag) {
        printf("Valid Python for-loop syntax!\n");
    } else {
        printf("Invalid syntax! Only for-loop syntax is allowed with proper indentation.\n");
    }

    return 0;
}
