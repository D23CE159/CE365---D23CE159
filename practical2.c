#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100
#define MAX_STATE_NAME_LEN 20

int main()
{
    int transitions[MAX_STATES][MAX_SYMBOLS];              // Transition table
    int num_states, num_symbols;                           // Number of states and symbols
    char state_names[MAX_STATES][MAX_STATE_NAME_LEN];      // State names
    char initial_state[MAX_STATE_NAME_LEN];                // Initial state of the automaton
    char accepting_states[MAX_STATES][MAX_STATE_NAME_LEN]; // Accepting states
    int num_accepting_states;                              // Number of accepting states
    char symbols[MAX_SYMBOLS];                             // Input symbols
    char input_string[100];                                // Input string to validate

    // Input the number of symbols and their respective characters
    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter input symbols: ");
    for (int i = 0; i < num_symbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    // Input the number of states and their names
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Enter state names: ");
    for (int i = 0; i < num_states; i++)
    {
        scanf("%s", state_names[i]);
    }

    // Input the initial state name
    printf("Enter initial state: ");
    scanf("%s", initial_state);

    // Input the number of accepting states and their names
    printf("Enter number of accepting states: ");
    scanf("%d", &num_accepting_states);

    printf("Enter accepting states: ");
    for (int i = 0; i < num_accepting_states; i++)
    {
        scanf("%s", accepting_states[i]);
    }

    // Input the transition table
    printf("Enter transition table:\n");
    for (int i = 0; i < num_states; i++)
    {
        for (int j = 0; j < num_symbols; j++)
        {
            printf("State %s to %c -> ", state_names[i], symbols[j]);
            char next_state[MAX_STATE_NAME_LEN];
            scanf("%s", next_state);

            // Find the index of the next state and update the transition table
            for (int k = 0; k < num_states; k++)
            {
                if (strcmp(state_names[k], next_state) == 0)
                {
                    transitions[i][j] = k;
                    break;
                }
            }
        }
    }

    // Input the string to be validated
    printf("Enter input string: ");
    scanf("%s", input_string);

    char current_state[MAX_STATE_NAME_LEN];
    strcpy(current_state, initial_state);

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
        int state_index = -1;
        for (int j = 0; j < num_states; j++)
        {
            if (strcmp(state_names[j], current_state) == 0)
            {
                state_index = j;
                break;
            }
        }

        if (state_index == -1)
        {
            printf("Invalid state transition\n");
            return 0;
        }

        strcpy(current_state, state_names[transitions[state_index][symbol_index]]);
    }

    // Check if the current state is an accepting state
    for (int i = 0; i < num_accepting_states; i++)
    {
        if (strcmp(accepting_states[i], current_state) == 0)
        {
            printf("Valid string\n");
            return 0;
        }
    }

    // If no accepting state is reached, the string is invalid
    printf("Invalid string\n");

    return 0;
}
