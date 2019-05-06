#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int dfs(int *colors, int *stack, int *k, edges *graf, int n, int cur_ver) {
    if (colors[cur_ver] == GRAY) {
        return 1;
    }
    colors[cur_ver] = GRAY;
    for (int i = 0; i < n; i++) {
        if (graf[i].from == cur_ver && colors[graf[i].to] != BLACK) {
            int err = dfs(colors, stack, k, graf, n, graf[i].to);
            if (err)
                return 1;
        }
    }

    colors[cur_ver] = BLACK;
    stack[*k] = cur_ver;
    *k += 1;
    return 0;
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

    edges *graf = malloc((unsigned int) n_edges * sizeof(edges));

    for (i = 0; i < n_edges; i++) {
        if (fscanf(f1, "%d %d", &graf[i].from, &graf[i].to) == 2) {
            if (graf[i].from < 1 || graf[i].from > n_vertices ||
                graf[i].to < 1 || graf[i].to > n_vertices) {
                free(graf);
                errors(5);
                return;
            }
        } else {
            errors(2);
            return;
        }

    }

    unsigned int k = 0;
    int *stack = malloc(n_vertices * sizeof(int));
    int *colors = malloc((n_vertices + 1) * sizeof(int));
    memset(colors, WHITE, sizeof(colors) * (n_vertices + 1));

    for (i = 1; i <= n_vertices; i++) {
        if (colors[i] == WHITE) {
            err = dfs(colors, stack, &k, graf, n_edges, i);
            if (err) {
                free(stack);
                free(colors);
                free(graf);
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
    free(graf);
}

int errors(int err) {
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
    return 1;
}

void print_help(void) {
    printf("Topsort: <inputfile> <outputfile>");
}