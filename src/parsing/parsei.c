#include "parsei.h" 
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_command(char* command) {
    int bufsize = 64, position = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    token = strtok(command, " \t\r\n");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }

        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return tokens;
}


int is_builtin(char* command) {
    return (strcmp(command, "cd") == 0 || strcmp(command, "echo") == 0 ||
            strcmp(command, "export") == 0 || strcmp(command, "jobs") == 0);
}

int has_pipe(char* command) {
    return (strchr(command, '|') != NULL);
}
