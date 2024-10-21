#ifndef EXECUTE_H
#define EXECUTE_H

void execute_command(char* command);
void handle_io_redirection(char* command);
void execute_background(char* command);

#endif
