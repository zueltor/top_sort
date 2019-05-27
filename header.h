#pragma once

#define WHITE 0
#define GRAY 1
#define BLACK 2
typedef struct edges edges;
struct edges {
    int from;
    int to;
};

typedef struct List List;
struct List{
    int v;
    List *next;
};

typedef struct Graph Graph;
struct Graph{
    int V;
    int E;
    List *Adj;
};

Graph *create_graph(unsigned int n_vertices, unsigned int n_edges);

void free_graph(Graph *G);

unsigned int visit(Graph *G, int *stack, int u, int *colors, int *i);

void topsort(char *in, char *out);

void errors(int err);

void print_help(void);