/*
 * scheduler.h
 * COMP 3500 Project 5 - CPU Scheduling
 * Author: Andrew Suggs (ads0127@auburn.edu)
 *
 * Statistics structure and the interface for the simulation mechanism and
 * the three scheduling policies.
 */
#ifndef SCHEDULER_H

#define SCHEDULER_H

#include "parser.h"

// waiting = turnaround - burst
// response = start - arrival
// turnaround = completion - arrival
struct stats {
    int total_waiting;
    int total_response;
    int total_turnaround;
    int busy_ticks;
    int total_time;
};

/* Run coordinator - create ready queue and then use specified algorithm */
int run_simulation(struct fields args, struct process *tasks, int num_tasks);

/* FCFS: next task is whichever arrived first (front of queue) */
int fcfs (struct process *ready[], int ready_count); /* returns 0 */

int rr (struct process *ready[], int ready_count);

int srtf (struct process *ready[], int ready_count);

/* Remove ready[i] by shifting everything after it down one slot */
void remove_at(struct process *ready[], int *ready_count, int i);

void print_statistics(struct stats s, int num_tasks);

#endif