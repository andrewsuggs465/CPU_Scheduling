#ifndef SCHEDULER_H

#define SCHEDULER_H

#include "parser.h"

/* Run coordinator - create ready queue and then use specified algorithm */
int run_simulation(struct fields args, struct process *tasks, int num_tasks);

int rr(struct process p);
int fcfs(struct process p);
int srtf(struct process p);

//int print_statistics(struct process *tasks);

#endif