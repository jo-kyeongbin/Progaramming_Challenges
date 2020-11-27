#include <stdio.h>
#include <stdbool.h>
#define NONE 333

bool visit[20] = {};
int d[20] = {};

void init_visit()
{
	for(int i=0;i<20;i++)
		visit[i] = false;
}

void add_map(int map[][20], int x, int y, int value)
{
	map[x][y] = value;
	map[y][x] = value;
}

void init_map(int map[][20])
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
				map[i][j] = NONE;
	}
}

int getSmallIndex(int v) {
	int min = NONE;
	int index = 0;
	for (int i =0; i < v; i++) {
		if(d[i] < min && !visit[i]) {
			min = d[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(int map[][20] ,int start, int v){
	for(int i =0; i < v; i++) {
		d[i] = map[start][i];
	}
	visit[start] = true;
	for(int i =0; i < v; i++) {
		int current = getSmallIndex(v);
		visit[current] = true;
		for(int j=0; j < v; j++) {
				if(d[current]+map[current][j] < d[j]) {
					d[j] = d[current]+map[current][j];
				}
		}
	}
}

int main()
{
	int map[20][20];
	int tcase;
	int result1,result2;
	int v,e;
	int start,mid,end;
	int x,y,value;

	while (scanf("%d",&tcase)!=EOF)
	{
		getchar();
		while (tcase>0)
		{
			scanf("%d %d",&v,&e);
			getchar();
			init_map(map);
			init_visit();
			while (e>0)
			{
				scanf("%d %d %d",&x,&y,&value);
				getchar();
				add_map(map,x-1,y-1,value);
				e--;
			}
			scanf("%d %d %d",&start,&mid,&end);
			getchar();
			dijkstra(map,start-1,v);
			result1 = d[mid-1];
			init_visit();
			dijkstra(map,mid-1,v);
			result2 = d[end-1];
			if (result1 == NONE || result2 == NONE)
				printf("-1\n");
			else
				printf("%d\n",result1+result2);
			tcase--;
		}
	}
}