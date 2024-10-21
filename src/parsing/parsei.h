#ifndef PARSEI_H
#define PARSEI_H

char** parse_command(char* input);
int is_builtin(char* command);
int has_pipe(char* command);

#endif
