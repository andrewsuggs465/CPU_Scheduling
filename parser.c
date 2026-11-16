#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


/* Print command-line usage */
static void print_usage(void) {
    fprintf(stderr, "Usage: scheduler task_list_file [FCFS|RR|SRTF] [time_quantum]\n");
}

struct fields parse_args(int argc, char *argv[]){
    struct fields f = {0};

    /* Input sanitization */
    if (argc > 4) {
        fprintf(stderr, "Too many arguments\n");
        print_usage();
        f.success = -1;
        return f;
    } else if (argc <= 2) {
        fprintf(stderr, "Too few arguments\n");
        print_usage();
        f.success = -1;
        return f;
    }

    /* Scheduling policy must be RR, FCFS, or SRTF */
    char *s_parse = argv[2];
    if (strcmp(s_parse, "FCFS") != 0 &&
        strcmp(s_parse, "RR") != 0 &&
        strcmp(s_parse, "SRTF") != 0) {
        fprintf(stderr, "Invalid scheduling policy\n");
        print_usage();
        f.success = -1;
        return f;
    }
    if (strcmp(s_parse, "FCFS") == 0) {
        f.policy = FCFS;
    }
    if (strcmp(s_parse, "RR") == 0) {
        f.policy = RR;
    }
    if (strcmp(s_parse, "SRTF") == 0) {
        f.policy = SRTF;
    }

    /* If time_quantum is left off for RR */
    if (argc == 3 && strcmp(s_parse, "RR") == 0) {
        fprintf(stderr, "Quantum must be used with RR\n");
        print_usage();
        f.success = -1;
        return f;
    }

    if (argc == 4) {
        /* If RR is selected: sanitize quantum, else argc=4 and not RR, give error */
        if (strcmp(s_parse, "RR") == 0) {
            /* Check that quantum is valid: >0, base 10, null terminator */
            char *end;
            long q = strtol(argv[3], &end, 10);

            if (end == argv[3] || *end != '\0' || q <= 0) {
                fprintf(stderr, "Invalid time quantum %s\n", argv[3]);
                print_usage();
                f.success = -1;
                return f;
            }
            f.quantum = q;
        } else {
            fprintf(stderr, "Quantum can only be used on RR\n");
            print_usage();
            f.success = -1;
            return f;
        }
    }
    f.success = 0;
    return f;
}

int parse_tasks(const char *file, struct process *tasks, int max_tasks) {
    FILE *fp;
    int linecount = 0;

    int n; // fscanf return value
    fp = fopen(file, "r");

    if (fp == NULL) {
        fprintf(stderr, "File does not exist!\n");
        return -1;
    }

    while ((linecount < max_tasks)) {
        n = fscanf(fp, "%d %d %d", &tasks[linecount].pid, &tasks[linecount].arrival, &tasks[linecount].burst);

        if (n == EOF) {
            break;
        }
        if (n != 3) {
            fprintf(stderr, "Invalid number of arguments in file!\n");
            fclose(fp);
            return -1;
        }
        for (int i = 0; i < linecount; i++) {
            if (tasks[i].pid == tasks[linecount].pid) {
                fprintf(stderr, "Process ID is not unique!\n");
                fclose(fp);
                return -1;
            }
        }
        if (tasks[linecount].arrival < 0) {
            fprintf(stderr, "Arrival cannot be negative!\n");
            fclose(fp);
            return -1;
        }
        if (tasks[linecount].burst <= 0) {
            fprintf(stderr, "Burst cannot be zero or negative!\n");
            fclose(fp);
            return -1;
        }
        tasks[linecount].start = -1;
        tasks[linecount].remaining = tasks[linecount].burst;
        linecount++;
    }

    if (linecount == max_tasks) {
        int extra_pid, extra_arrival, extra_burst;
        if(fscanf(fp, "%d %d %d", &extra_pid, &extra_arrival, &extra_burst) != EOF) {
            fprintf(stderr, "Too many tasks (max %d)!\n", max_tasks);
            fclose(fp);
            return -1;
        }
    }
    
    if (linecount == 0) {
        fprintf(stderr, "Task file is empty!\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return linecount;
}