#pragma once

#define WHITE 0
#define GRAY 1
#define BLACK 2
typedef struct edges edges;
struct edges {
    int from;
    int to;
};

unsigned int dfs(int *colors, int *stack, int *k, edges *graf, int n, int cur_ver);

void topsort(char *in, char *out);

int errors(int err);

void print_help(void);