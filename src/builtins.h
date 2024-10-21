#ifndef BUILTINS_H
#define BUILTINS_H

void builtin_cd(char* path);
void builtin_pwd();
void builtin_export(char* var, char* value);
void builtin_echo(char** args);
void builtin_jobs();

// Add the missing execute_builtin function prototype
void execute_builtin(char** args);

#endif
