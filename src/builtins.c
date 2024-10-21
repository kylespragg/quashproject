#include "builtins.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void builtin_cd(char* path) {
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
