// DFA
#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

int main()
{
    int transitions[MAX_STATES][MAX_SYMBOLS];               // Transition table
    int num_states, num_symbols;                            // Number of states and symbols
    int initial_state;                                      // Initial state of the automaton
    int accepting_states[MAX_STATES], num_accepting_states; // Accepting states and their count
    char symbols[MAX_SYMBOLS];                              // Input symbols
    char input_string[100];                                 // Input string to validate

    // Input the number of symbols and their respective characters
    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter input symbols: ");
    for (int i = 0; i < num_symbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    // Input the number of states in the automaton
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    // Input the initial state of the automaton
    printf("Enter initial state: ");
    scanf("%d", &initial_state);

    // Input the number of accepting states and their values
    printf("Enter  number of accepting states: ");
    scanf("%d", &num_accepting_states);

    printf("Enter accepting state: ");
    for (int i = 0; i < num_accepting_states; i++)
    {
        scanf("%d", &accepting_states[i]);
    }

    // Input the transition table for each state and symbol
    printf("Enter transition table:\n");
    for (int i = 0; i < num_states; i++)
    {
        for (int j = 0; j < num_symbols; j++)
        {
            printf("State %d to %c -> ", i + 1, symbols[j]);
            scanf("%d", &transitions[i][j]);
        }
    }

    // Input the string to be validated
    printf("Enter input string: ");
    scanf("%s", input_string);

    int current_state = initial_state;
    // Process each character in the input string
    for (int i = 0; input_string[i] != '\0'; i++)
    {
        char symbol = input_string[i];
        int symbol_index = -1;

        // Find the index of the current symbol in the input symbols
        for (int j = 0; j < num_symbols; j++)
        {
            if (symbols[j] == symbol)
            {
                symbol_index = j;
                break;
            }
        }

        // If the symbol is invalid, terminate and output an error
        if (symbol_index == -1)
        {
            printf("Invalid string\n");
            return 0;
        }

        // Update the current state based on the transition table
        current_state = transitions[current_state - 1][symbol_index];
    }

    // Check if the current state is an accepting state
    for (int i = 0; i < num_accepting_states; i++)
    {
        if (accepting_states[i] == current_state)
        {
            printf("Valid string\n");
            return 0;
        }
    }

    // If no accepting state is reached, the string is invalid
    printf("Invalid string\n");

    return 0;
}