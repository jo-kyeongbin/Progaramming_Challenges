#include <stdbool.h>
#include <stdio.h>

int V;
int key;
void printSolution(int color[]);

bool isSafe(bool graph[10][10], int color[])
{
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			if (graph[i][j] && color[j] == color[i])
				return false;
	return true;
}

bool graphColoring(bool graph[][10], int m, int i,int color[10])
{
	if (i == V) {
		if (isSafe(graph, color)) {
			key = 1;
			printSolution(color);
		}
		return false;
	}
	for (int j = 1; j <= m; j++) {
		color[i] = j;
		graphColoring(graph, m, i + 1, color);
		color[i] = 0;
	}

	return false;
}
void printSolution(int color[])
{
    for (int i = 0; i < V-1; i++)
        printf("%d ", color[i]);
    printf("%d \n",color[V-1]);
}

int main()
{
	bool graph[10][10];
    int m;
    int i,j,k;
	char buf[1024];
	while(scanf("%d %d",&V,&m)!=EOF)
	{
		getchar();
		for(i=0;i<V;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<V;j++)
			{
				graph[i][j] = buf[k]-'0';
				k+=2;
			}
		}
		int color[V];
		for (int i = 0; i < V; i++)
			color[i] = 0;
		key = 0;
		graphColoring(graph, m, 0, color);
		if (key == 0)
			printf("NONE\n");
	}
	return 0;
}
