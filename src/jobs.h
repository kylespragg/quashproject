#ifndef JOBS_H
#define JOBS_H

void add_job(int pid, char* command);
void remove_job(int pid);
void print_jobs();

#endif
