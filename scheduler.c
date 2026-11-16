#include <stdio.h>
#include "parser.h"

#define MAX_TASKS 100

int main(int argc, char *argv[]) {
    int num_tasks;
    struct fields args = parse_args(argc, argv);
    if (args.success != 0) {
        fprintf(stderr, "Command failed to parse!");
        return -1;
    }
    
    struct process tasks[MAX_TASKS];

    num_tasks = parse_tasks(argv[1], tasks, MAX_TASKS);
    if (num_tasks == -1) {
        return -1;
    }

    return 0;
}