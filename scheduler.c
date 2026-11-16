/*
 * scheduler.c
 * COMP 3500 Project 5 - CPU Scheduling
 * Author: Andrew Suggs (ads0127@auburn.edu)
 *
 * Time-driven scheduling mechanism (run_simulation) and the three
 * scheduling policies (fcfs, rr, srtf). Each policy only picks an index
 * into the ready queue; run_simulation does the arrivals, preemption,
 * dispatch, bookkeeping, and output.
 */
#include <stdio.h>
#include <limits.h>
#include "scheduler.h"

int run_simulation(struct fields args, struct process *tasks, int num_tasks){
    int finished = 0;
    int ready_count = 0;
    /* Counts how many times current has run since its last dispatch */
    int slice_used = 0;
    struct process *ready[num_tasks];
    struct process *current = NULL;
    struct stats s = {0};
    
    for (int t = 0; ; t++) {
        /* Move tasks that have arrived into ready queue */
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].arrival == t) {
                ready[ready_count] = &tasks[i];
                ready_count++;
            }
        }
        /* Current finished? */
        if (current != NULL) {
            if (current->remaining == 0) {
                printf("<time %d> process %d is finished...\n", t, current->pid);
                slice_used = 0;
                int turnaround = t - current->arrival;
                s.total_turnaround += turnaround;
                int waiting = turnaround - current->burst;
                s.total_waiting += waiting;
                finished++;
                current = NULL;
            } else if (args.policy == RR ) {
                slice_used++;
                if (slice_used == args.quantum) {
                    slice_used = 0;
                    ready[ready_count] = current;
                    current = NULL;
                    ready_count++;
                }
            } else if (args.policy == SRTF) {
                int i;
                i = srtf(ready, ready_count);
                if (i > -1) {
                    if (ready[i]->remaining < current->remaining) {
                        ready[ready_count] = current;
                        current = NULL;
                        ready_count++;
                    }
                }
                
            }
        }
        
        /* All done */
        if (finished == num_tasks) {
            printf("<time %d> All processes finish ......\n", t);
            s.total_time = t;
            print_statistics(s, num_tasks);
            break;
        }
        /* Dispatch selected policy */
        if (current == NULL && ready_count > 0) {
            int i = -1;
            switch (args.policy) {
                case FCFS: i = fcfs(ready, ready_count); break;
                case RR:   i =   rr(ready, ready_count); break;
                case SRTF: i = srtf(ready, ready_count); break;
            }
            if (i < 0 || i >= ready_count) {
                fprintf(stderr, "Error in dispatch.\n");
                return -1;
            }
            current = ready[i];
            remove_at(ready, &ready_count, i);
        }

        /* Simulate running a process */
        if (current != NULL) {
            printf("<time %d> process %d is running\n", t, current->pid);
            if (current->remaining == current->burst) {
                int response = t - current->arrival;
                s.total_response += response;
            }
            current->remaining--;
            s.busy_ticks++;
        } else {
            printf("<time %d> idle\n", t);
        }
    }
    return 0;
}

int fcfs (struct process *ready[], int ready_count) {
    (void)ready;
    (void)ready_count;
    return 0;
}

int rr (struct process *ready[], int ready_count) {
    (void)ready;
    (void)ready_count;
    return 0;
}

int srtf (struct process *ready[], int ready_count) {
    int shortest_remaining = INT_MAX;
    int pos = -1;
    for (int i = 0; i < ready_count; i++) {
        if (ready[i]->remaining < shortest_remaining) {
            shortest_remaining = ready[i]->remaining;
            pos = i;
        }
    }
    return pos;
}

void remove_at(struct process *ready[], int *ready_count, int i) {
    for (int j = i; j < *ready_count - 1; j++) {
        ready[j] = ready[j + 1];
    }
    (*ready_count)--;
}

void print_statistics(struct stats s, int num_tasks) {
    /* Final averages to be reported */
    double avg_wait = (double)s.total_waiting    / num_tasks;
    double avg_resp = (double)s.total_response   / num_tasks;
    double avg_turn = (double)s.total_turnaround / num_tasks;
    double cpu = 0.0;
    if (s.total_time != 0) cpu = 100.0 * s.busy_ticks / s.total_time;
    
    printf("============================================================\n");
    printf("Average waiting time:    %.2f\n", avg_wait);
    printf("Average response time:   %.2f\n", avg_resp);
    printf("Average turnaround time: %.2f\n", avg_turn);
    printf("Overall CPU usage:       %.2f%%\n", cpu);
    printf("============================================================\n");
}