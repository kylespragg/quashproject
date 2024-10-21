#include "builtins.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void builtin_cd(char* path) {
    if (path == NULL) {
        path = getenv("HOME");
    }
    
    if (chdir(path) != 0) {
        perror("quash: cd");
    }
}


void builtin_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("quash: pwd");
    }
}

void builtin_export(char* var, char* value) {
    if (setenv(var, value, 1) != 0) {
        perror("quash: export");
    }
}

void builtin_echo(char** args) {
    int i = 1;
    while (args[i] != NULL) {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}

void builtin_jobs() {
    print_jobs();
}

// Add the missing execute_builtin function
void execute_builtin(char** args) {
    if (strcmp(args[0], "cd") == 0) {
        builtin_cd(args[1]);
    } else if (strcmp(args[0], "pwd") == 0) {
        builtin_pwd();
    } else if (strcmp(args[0], "export") == 0) {
        builtin_export(args[1], args[2]);
    } else if (strcmp(args[0], "echo") == 0) {
        builtin_echo(args);
    } else if (strcmp(args[0], "jobs") == 0) {
        builtin_jobs();
    } else {
        fprintf(stderr, "quash: command not found: %s\n", args[0]);
    }
}
