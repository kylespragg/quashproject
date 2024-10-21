#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

char* get_absolute_path(char* relative_path) {
    char* absolute_path = realpath(relative_path, NULL);
    if (absolute_path == NULL) {
        perror("quash: get_absolute_path");
    }
    return absolute_path;
}
