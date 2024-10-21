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
    char** args = parse_command(command);  // Assuming parse_command splits the command into args properly
    
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
        pid_t pid = fork();
        if (pid == 0) {
            handle_io_redirection(command);
            // Ensure args[0] is the command (e.g., "ls") and args[1..n] are its parameters.
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
