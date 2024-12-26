#include <stdio.h>
#include <string.h>

int main()
{
    int option;

    // Loop to keep showing the menu until the user exits
    while (1)
    {
        printf("\nOptions:\n");
        printf("1. Check if a string matches the pattern 'a*bb'\n");
        printf("2. Quit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        if (option == 1)
        {

            // Array to store the input string
            char str[500];

            printf("Enter a string: ");
            scanf("%s", str);

            // Find the string length
            int length = strlen(str);

            // Pointer to traverse the string
            int index = 0;

            // Skip all consecutive 'a' characters
            while (str[index] == 'a')
            {
                index++; //
            }

            // Ensure the remaining part is "bb" and nothing more
            if (str[index] == 'b' && str[index + 1] == 'b' && str[index + 2] == '\0')
            {
                printf("String is valid.\n");
            }
            else
            {
                printf("String is invalid.\n");
            }
        }
        else if (option == 2)
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid input. Please select again.\n");
        }
    }

    return 0;
}