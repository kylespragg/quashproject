#include "execute.h"
#include "parsing/parsei.h"  // Updated include to match the new name
#include "builtins.h"
#include "jobs.h"
#include "utils.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(char* command) {
    if (is_builtin(command)) {
        execute_builtin(command);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            handle_io_redirection(command);
            char** args = parse_command(command);
            if (execvp(args[0], args) == -1) {
                perror("quash");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("quash");
        } else {
            wait(NULL);
        }
    }
}

void handle_io_redirection(char* command) {
    char* output_file = strstr(command, ">");
    if (output_file != NULL) {
        *output_file = '\0';
        output_file = strtok(output_file + 1, " ");
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("quash");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void execute_background(char* command) {
    pid_t pid = fork();
    if (pid == 0) {
        setpgid(0, 0);
        execute_command(command);
        exit(EXIT_SUCCESS);
    } else {
        add_job(pid, command);
        printf("[Job %d] %s\n", pid, command);
    }
}
