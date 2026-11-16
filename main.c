/*
 * main.c
 * COMP 3500 Project 5 - CPU Scheduling
 * Author: Andrew Suggs (ads0127@auburn.edu)
 *
 * Entry point for the scheduler. Parses the command line, loads the task
 * list, prints the banner, and runs the simulation.
 *
 * Usage: scheduler task_list_file [FCFS|RR|SRTF] [time_quantum]
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scheduler.h"

#define MAX_TASKS 100

/* Policy names, indexed by enum scheduling_policy */
static const char *policy_names[] = { "FCFS", "RR", "SRTF" };

int main(int argc, char *argv[]) {
    int num_tasks;
    struct fields args = parse_args(argc, argv);
    if (args.success != 0) {
        return EXIT_FAILURE;
    }

    struct process tasks[MAX_TASKS];

    num_tasks = parse_tasks(argv[1], tasks, MAX_TASKS);
    if (num_tasks == -1) {
        return EXIT_FAILURE;
    }

    printf("Scheduling Policy: %s\n", policy_names[args.policy]);
    printf("There are %d tasks loaded from \"%s\".\n", num_tasks, argv[1]);
    printf("==================================================================\n");

    if (run_simulation(args, tasks, num_tasks) == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
