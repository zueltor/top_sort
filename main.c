#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rebro rebro;
struct rebro {
	int from;
	int to;
};


unsigned int dfs(int *colors, int *stack, int *k, rebro *graf, int n, int cur_ver)
{
	if (colors[cur_ver] == 1)
	{
		return 1;
	}
	colors[cur_ver] = 1;
	for (int i = 0; i < n; i++)
	{
		if (graf[i].from == cur_ver && colors[graf[i].to] != 2)
		{
			int err = dfs(colors, stack, k, graf, n, graf[i].to);
			if (err)
				return 1;
		}
	}

	colors[cur_ver] = 2;
	stack[*k] = cur_ver;
	*k = *k + 1;
	return 0;
}

int main(void)
{
	int n_vertices,
		n_edges,
		i;
	unsigned int err;


	if (scanf_s("%d", &n_vertices) == 1)
	{
		if (n_vertices < 0 || n_vertices > 1000)
		{
			printf("bad number of vertices");
			return 0;
		}
	}
	else 
	{
		printf("bad number of lines"); 
		return 0;
	}

	if (scanf_s("%d", &n_edges) != 1)
	{
		printf("bad number of lines");
		return 0;
	}
	if (n_edges < 0 || n_edges > n_vertices * (n_vertices - 1) / 2)
	{
		printf("bad number of edges");
		return 0;
	}

	rebro *graf = malloc((unsigned int)n_edges * sizeof(rebro));

	for (i = 0; i < n_edges; i++)
	{
		if (scanf_s("%d %d", &graf[i].from, &graf[i].to) == 2) 
		{
			if (graf[i].from < 1 || graf[i].from>n_vertices ||
				graf[i].to < 1 || graf[i].to > n_vertices)
			{
				printf("bad vertex");
				free(graf);
				return 0;
			}
		}
		else 
		{
			printf("bad number of lines");
			return 0;
		}

	}
	unsigned int k = 0;
	int *stack = malloc(n_vertices * sizeof(int));
	int *colors = malloc((n_vertices + 1) * sizeof(int));
	memset(colors, 0, sizeof(colors) * (n_vertices + 1));

	for (i = 1; i <= n_vertices; i++)
	{
		if (colors[i] == 0)
		{
			err = dfs(colors, stack, &k, graf, n_edges, i);
			if (err)
			{
				printf("impossible to sort");
				free(stack);
				free(colors);
				free(graf);
				return 0;
			}
		}
	}
	for (i = k - 1; i >= 0;i--)
	{
		printf("%d ", stack[i]);
	}
	free(stack);
	free(colors);
	free(graf);
	return 0;
}