#include "jobs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    char* command;
} Job;

Job jobs[64];  // Array to store jobs
int job_count = 0;

void add_job(int pid, char* command) {
    jobs[job_count].pid = pid;
    jobs[job_count].command = strdup(command);
    job_count++;
}

void remove_job(int pid) {
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].pid == pid) {
            free(jobs[i].command);
            for (int j = i; j < job_count - 1; j++) {
                jobs[j] = jobs[j + 1];
            }
            job_count--;
            return;
        }
    }
}

void print_jobs() {
    for (int i = 0; i < job_count; i++) {
        printf("[%d] %s\n", jobs[i].pid, jobs[i].command);
    }
}
