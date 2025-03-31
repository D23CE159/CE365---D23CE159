%{

#include <stdio.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c);
char pop();
int is_matching_pair(char open, char close);
void check_matching(const char *input);

%}

%option noyywrap

%%

[(){}\[\]]+	{ check_matching(yytext); }
.	{}

%%

void push(char c){
	if (top < MAX - 1) {
		stack[++top] = c;
	}
}

char pop() {
	if (top >= 0) {
		return stack[top--];
	}
	return '\0';
}

int is_matching_pair(char open, char close) {
	return (open == '(' && close == ')') ||
		(open == '{' && close == '}') ||
		(open == '[' && close == ']');
}

void check_matching(const char *input) {
	top = -1;
	for (int i = 0; input[i] != '\0'; i++) {
		char c = input[i];
		if (c == '(' || c == '{' || c == '[') {
			push(c);
		} else if (c == ')' || c == '}' || c == ']') {
			if (top == -1 || !is_matching_pair(pop(), c)) {
				printf("Unbalanced: %s\n", input);
				return;
			}
		}
	}
	if (top == -1) {
		printf("Balanced: %s\n", input);
	} else {
		printf("Unbalanced: %s\n", input);
	}
}

int main() {
	printf("Enter parentheses expressions (Ctrl + D to stop):\n");
	yylex();
	return 0;
}