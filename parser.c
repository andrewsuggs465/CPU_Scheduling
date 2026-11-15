#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

/* Print command-line usage */
static void print_usage(void) {
    printf("Usage: scheduler task_list_file [FCFS|RR|SRTF] [time_quantum]\n");
}

struct fields parse_args(int argc, char *argv[]){
    struct fields f = {0};

    /* Input sanitization */
    if (argc > 4) {
        printf("Too many arguments\n");
        print_usage();
        f.success = -1;
        return f;
    } else if (argc <= 2) {
        printf("Too few arguments\n");
        print_usage();
        f.success = -1;
        return f;
    }

    /* Scheduling policy must be RR, FCFS, or SRTF */
    char *s_parse = argv[2];
    if (strcmp(s_parse, "FCFS") != 0 &&
        strcmp(s_parse, "RR") != 0 &&
        strcmp(s_parse, "SRTF") != 0) {
        printf("Invalid scheduling policy\n");
        print_usage();
        f.success = -1;
        return f;
    }
    if (strcmp(s_parse, "FCFS") == 0) {
        f.policy = 0;
    }
    if (strcmp(s_parse, "RR") == 0) {
        f.policy = 1;
    }
    if (strcmp(s_parse, "SRTF") == 0) {
        f.policy = 2;
    }

    /* If time_quantum is left off for RR */
    if (argc == 3 && strcmp(s_parse, "RR") == 0) {
        printf("Quantum must be used with RR\n");
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
                printf("Invalid time quantum %s\n", argv[3]);
                print_usage();
                f.success = -1;
                return f;
            }
            f.quantum = q;
        } else {
            printf("Quantum can only be used on RR\n");
            print_usage();
            f.success = -1;
            return f;
        }
    }
    f.success = 0;
    return f;
}