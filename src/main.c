#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include your header files for the various components of your shell
#include "execute.h"  // For execute_command()
#include "parsei.h"   // For parse_command()
#include "builtins.h" // For is_builtin(), execute_builtin()

#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];  // Buffer to store the input
    char *parsed_command;        // Placeholder for the parsed command

    printf("Welcome to Quash Shell! Type 'exit' to quit.\n");

    while (1) {
        printf("quash> ");  // Shell prompt
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        // Remove newline character at the end of input
        input[strcspn(input, "\n")] = 0;

        // Exit the shell if the user types "exit"
        if (strcmp(input, "exit") == 0) {
            printf("Exiting Quash Shell...\n");
            break;
        }

        // Parse the input command
        parsed_command = parse_command(input);

        // If the command is a built-in, execute it directly
        if (is_builtin(parsed_command)) {
            execute_builtin(parsed_command);
        } else {
            // Otherwise, pass the command to execute_command()
            execute_command(parsed_command);
        }
    }

    return 0;
}
