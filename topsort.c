#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int visit(Graph *G, int *stack, int u, int *colors, int *i) {
    if (colors[u] == GRAY) {
        return 1;
    }

    colors[u]=GRAY;
    List *p=G->Adj[u].next;
    while (p!=NULL) {
        if (colors[p->v]!=BLACK){
            if (visit(G,stack,p->v,colors,i))
                return 1;
        }
        p=p->next;
    }
    stack[*i]=u;
    *i+=1;

    colors[u] = BLACK;
    return 0;
}

Graph *create_graph(unsigned int n_vertices, unsigned int n_edges) {
    int i;
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->V = n_vertices;
    G->E = n_edges;
    G->Adj = (List *) malloc((G->V + 1) * sizeof(List));
    for (i = 1; i <= G->V; i++) {
        G->Adj[i].v = i;
        G->Adj[i].next = NULL;
    }
    return G;
}

void topsort(char *in, char *out) {
    int n_vertices,
            n_edges,
            i;
    unsigned int err;

    FILE *f1 = fopen(in, "rb");
    FILE *f2 = fopen(out, "wb");
    if (f1 == NULL) {
        errors(1);
        return;
    }
    if (f2 == NULL) {
        errors(1);
        return;
    }
    fseek(f1, 0, SEEK_END);
    int size = ftell(f1);
    if (size == 0) {
        errors(2);
        return;
    }
    fseek(f1, 0, SEEK_SET);

    if (fscanf(f1, "%d", &n_vertices)) {
        if (n_vertices < 0 || n_vertices > 1000) {
            errors(3);
            return;
        }
    } else {
        errors(2);
        return;
    }

    if (fscanf(f1, "%d", &n_edges) != 1) {
        errors(2);
        return;
    }
    if (n_edges < 0 || n_edges > n_vertices * (n_vertices - 1) / 2) {
        errors(4);
        return;
    }

    Graph *G=create_graph(n_vertices,n_edges);

    int v1,v2;
    List *tmp;

    for (i = 0; i < G->E; i++) {
        if (fscanf(f1, "%d %d", &v1, &v2) == 2) {
            if (v1 < 1 || v1 > G->V || v2 < 1 || v2 > G->V) {
                free_graph(G);
                errors(5);
                return;
            }
        } else {
            free_graph(G);
            errors(2);
            return;
        }
        tmp = (List *) malloc(sizeof(List));
        tmp->v = v2;
        tmp->next = G->Adj[v1].next;
        G->Adj[v1].next = tmp;
    }

    unsigned int k = 0;
    int *stack = malloc(n_vertices * sizeof(int));
    int *colors = malloc((n_vertices + 1) * sizeof(int));
    memset(colors, WHITE, sizeof(colors) * (n_vertices + 1));

    for (i = 1; i <= G->V; i++) {
        if (colors[i] == WHITE) {
            err = visit(G,stack, i, colors, &k);
            if (err) {
                free(stack);
                free(colors);
                free_graph(G);
                errors(6);
                return;
            }
        }
    }

    for (i = k - 1; i >= 0; i--) {
        fprintf(f2, "%d ", stack[i]);
    }

    free(stack);
    free(colors);
    free_graph(G);
    fclose(f1);
    fclose(f2);
}

void free_graph(Graph *G) {
    unsigned int i;
    free(G->Adj);
    free(G);
}

void errors(int err) {
    switch (err) {
        case 1:
            printf("file cannot be opened");
        case 2:
            printf("bad number of lines");
        case 3:
            printf("bad number of vertices");
        case 4:
            printf("bad number of edges");
        case 5:
            printf("bad vertex");
        case 6:
            printf("impossible to sort");
        default:;
    }
}

void print_help(void) {
    printf("Topsort: <inputfile> <outputfile>");
}