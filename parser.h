#ifndef PARSER_H

#define PARSER_H

enum scheduling_policy{
    FCFS,
    RR,
    SRTF,
};

struct fields {
    int success;
    enum scheduling_policy policy;
    int quantum;
};


struct fields parse_args(int argc, char *argv[]);

#endif