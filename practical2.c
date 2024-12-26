// DFA
#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

int main()
{
    int transitions[MAX_STATES][MAX_SYMBOLS];
    int num_states, num_symbols;
    int initial_state;
    int accepting_states[MAX_STATES], num_accepting_states;
    char symbols[MAX_SYMBOLS];
    char input_string[100];

    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter input symbols: ");
    for (int i = 0; i < num_symbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Enter initial state: ");
    scanf("%d", &initial_state);

    printf("Enter  number of accepting states: ");
    scanf("%d", &num_accepting_states);

    printf("Enter accepting state: ");
    for (int i = 0; i < num_accepting_states; i++)
    {
        scanf("%d", &accepting_states[i]);
    }

    printf("Enter transition table:\n");
    for (int i = 0; i < num_states; i++)
    {
        for (int j = 0; j < num_symbols; j++)
        {
            printf("State %d to %c -> ", i + 1, symbols[j]);
            scanf("%d", &transitions[i][j]);
        }
    }

    printf("Enter input string: ");
    scanf("%s", input_string);

    int current_state = initial_state;
    for (int i = 0; input_string[i] != '\0'; i++)
    {
        char symbol = input_string[i];
        int symbol_index = -1;

        for (int j = 0; j < num_symbols; j++)
        {
            if (symbols[j] == symbol)
            {
                symbol_index = j;
                break;
            }
        }

        if (symbol_index == -1)
        {
            printf("Invalid string\n");
            return 0;
        }

        current_state = transitions[current_state - 1][symbol_index];
    }

    for (int i = 0; i < num_accepting_states; i++)
    {
        if (accepting_states[i] == current_state)
        {
            printf("Valid string\n");
            return 0;
        }
    }

    printf("Invalid string\n");

    return 0;
}