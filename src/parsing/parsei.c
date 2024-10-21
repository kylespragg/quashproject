#include "parsei.h" 
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_command(char* input) {
    char** args = malloc(64 * sizeof(char*)); // Allocate memory for command arguments
    char* token;
    int position = 0;

    if (!args) { // Check if memory allocation was successful
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \t\r\n\a");
    while (token != NULL) {
        args[position] = token;
        position++;
        token = strtok(NULL, " \t\r\n\a");
    }
    args[position] = NULL; // Null-terminate the array of arguments
    return args;
}

int is_builtin(char* command) {
    return (strcmp(command, "cd") == 0 || strcmp(command, "echo") == 0 ||
            strcmp(command, "export") == 0 || strcmp(command, "jobs") == 0);
}

int has_pipe(char* command) {
    return (strchr(command, '|') != NULL);
}
