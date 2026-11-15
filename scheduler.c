#include <stdio.h>
#include "parser.h"

// waiting = turnaround - burst
// response = start - arrival
// turnaround = completion - arrival

struct process {
    int pid;
    int arrival;
    int burst;
    int start;
    int remaining;
};



int main(int argc, char *argv[]) {
    struct fields args = parse_args(argc, argv);
    if (args.success != 0){
        return -1;
    }
    printf("Success!");
    return 0;
}