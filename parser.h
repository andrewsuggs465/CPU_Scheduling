#ifndef PARSER_H

#define PARSER_H

// waiting = turnaround - burst
// response = start - arrival
// turnaround = completion - arrival

/*
* The structure for each process
* - pid is a unique numeric process ID
* - arrival_time is the time instance at which a task arrives
* - burst_time is the CPU time requested by a task
* - start is the time the process starts
* - remaining is the time left if preempted
*/
struct process {    
    int pid;
    int arrival;
    int burst;
    int start;
    int remaining;
};

/* 
* The scheduling policy must be
* - First-Come First-Serve
* - Round-Robin
* - Shortest Remaining Time First
*/
enum scheduling_policy{
    FCFS,
    RR,
    SRTF,
};

/*
* Holds fields for parsing the command line arguments
* - Success: whether or not the given function succeeded
* - Policy: enum from before
* - Quantum: RR active CPU time 
*/
struct fields {
    int success;
    enum scheduling_policy policy;
    int quantum;
};

/* 
* Parse command-line arguments 
* - Check for input validity and sanitize quantum
* - Check bounds
* - Assign scheduling_policy and quantum
*/
struct fields parse_args(int argc, char *argv[]);

/*
* Read file given a tasks array and max_tasks. Returns -1 or number of tasks read.
* The task information will be read from an input text file, the format of which is
* pid arrival_time burst_time
*
* The time unit of arrival_time, burst_time, and interval is millisecond.
*/
int parse_tasks(const char *file, struct process *tasks, int max_tasks);
#endif