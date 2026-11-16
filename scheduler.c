#include "scheduler.h"

/* Running totals */
int total_waiting_time = -1;
int total_response_time = -1;
int total_turnaround_time = -1;
int total_cpu_usage = -1;

/* Final averages to be reported */
int average_waiting_time = -1;
int average_response_time = -1;
int average_turnaround_time = -1;
int overall_cpu_usage = -1;

int run_simulation(struct fields args, struct process *tasks, int num_tasks){
    struct process *ready[num_tasks];
    int ready_count = 0;

    for (int t = 0; ; t++) {
        /* Move tasks that have arrived into ready queue */
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].arrival == t) {
                ready[ready_count] = &tasks[i];
                ready_count++;
    
            }
        }
        struct process *current = NULL;
        if (current.remaining == 0) {
            
            current = NULL;
        }
    }
    return 0;
}