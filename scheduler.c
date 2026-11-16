#include <stdio.h>
#include "scheduler.h"

int run_simulation(struct fields args, struct process *tasks, int num_tasks){
    int finished = 0;
    int ready_count = 0;
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
        if (current != NULL && current->remaining == 0) {
            printf("<time %d> process %d finished\n", t, current->pid);
            finished++;
            current = NULL;
        }
        /* All done */
        if (finished == num_tasks) {
            printf("<time %d> All processess finished\n", t);
            s.total_time = t;
            print_statistics(s, nym_tasks);
            break;
        }
        /* Dispatch selected policy */
        if (current == NULL && ready_count > 0) {
            int i;
            switch (args.policy) {
                case FCFS: i = fcfs(ready, ready_count); break;
                case RR:   i =   rr(ready, ready_count); break;
                case SRTF: i = srtf(ready, ready_count); break;
            }
            current = ready[i];
            remove_at(ready, &ready_count, i);
        }

        if (current != NULL) {
            printf("<time %d> process %d is running\n", t, current->pid);
            current->remaining--;
            s.busy_ticks++;
        } else {
            printf("<time %d> idle\n", t);
        }
    }
    return 0;
}

int fcfs (struct process *ready[], int ready_count) {
    return 0;
}

int rr (struct process *ready[], int ready_count) {

}

int srtf (struct process *ready[], int ready_count) {

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