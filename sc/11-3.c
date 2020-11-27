#include <stdio.h>
#define ABS(x) (((x)<0)?-(x):(x))

typedef struct highest{
	int x;
	int y;
	int time;
} highest;

int H,T;
int row,col;
int h,t;
int visited[10][10];
highest save[100];
int try;
int backup;


void init_visit()
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			visited[i][j] = 0;
}

int go_index(int map[][10] ,int x, int y, int *l)
{
	int min = 26;
	int c = map[x][y];
	if (x-1>=0 && visited[x-1][y] == 0)
	{
		if(min > map[x-1][y] && c <= map[x-1][y] && map[x-1][y] - c <= H)
		{
			min = map[x-1][y];
			l[0] = x-1;
			l[1] = y;
		}
	}
	if (x+1<row && visited[x+1][y] == 0)
	{
		if (min > map[x+1][y] && c <= map[x+1][y] && map[x+1][y] - c <= H)
		{
			min = map[x+1][y];
			l[0] = x+1;
			l[1] = y;
		}
	}
	if (y-1>=0 && visited[x][y-1] == 0)
	{
		if (min > map[x][y-1] && c <= map[x][y-1] && map[x][y-1] - c <= H)
		{
			min = map[x][y-1];
			l[0] = x;
			l[1] = y-1;
		}
	}
	if (y+1<col && visited[x][y+1] == 0)
	{
		if (min > map[x][y+1] && c <= map[x][y+1] && map[x][y+1] - c <= H)
		{
			min = map[x][y+1];
			l[0] = x;
			l[1] = y+1;
		}
	}
	if (x+1<row && y-1>=0 && visited[x+1][y-1] == 0)
	{
		if (min > map[x+1][y-1] && c <= map[x+1][y-1] && map[x+1][y-1] - c <= H)
		{
			min = map[x+1][y-1];
			l[0] = x+1;
			l[1] = y-1;
		}
	}
	if (x+1<row && y+1<col && visited[x+1][y+1] == 0)
	{
		if (min > map[x+1][y+1] && c <= map[x+1][y+1] && map[x+1][y+1] - c <= H)
		{
			min = map[x+1][y+1];
			l[0] = x+1;
			l[1] = y+1;
		}
	}
	if (x-1>=0 && y-1>=0 && visited[x-1][y-1] == 0)
	{
		if (min > map[x-1][y-1] && c <= map[x-1][y-1] && map[x-1][y-1] - c <= H)
		{
			min = map[x-1][y-1];
			l[0] = x-1;
			l[1] = y-1;
		}
	}
	if (x-1>=0 && y+1<col && visited[x-1][y+1] == 0)
	{
		if (min > map[x-1][y+1] && c <= map[x-1][y+1] && map[x-1][y+1] - c <= H)
		{
			min = map[x-1][y+1];
			l[0] = x-1;
			l[1] = y+1;
		}
	}
	if (min == 26)
		return 0;
	else
		return 1;
}

int back_index(int map[][10],int x, int y, int *l)
{
	int min = 26;
	int c = map[x][y];
	if (x-1>=0 && visited[x-1][y] == 0)
	{
		if(map[x-1][y] <= c && ABS(map[x-1][y] - c) <= H && min > map[x-1][y])
		{
			min = map[x-1][y];
			l[0] = x-1;
			l[1] = y;
		}
	}
	if (x+1<row && visited[x+1][y] == 0)
	{
		if(map[x+1][y] <= c && ABS(map[x+1][y] - c) <= H && min > map[x+1][y])
		{
			min = map[x+1][y];
			l[0] = x+1;
			l[1] = y;
		}
	}
	if (y-1>=0 && visited[x][y-1] == 0)
	{
		if(map[x][y-1] <= c && ABS(map[x][y-1] - c) <= H && min > map[x][y-1])
		{
			min = map[x][y-1];
			l[0] = x;
			l[1] = y-1;
		}
	}
	if (y+1<col && visited[x][y+1] == 0)
	{
		if(map[x][y+1] <= c && ABS(map[x][y+1] - c) <= H && min > map[x][y+1])
		{
			min = map[x][y+1];
			l[0] = x;
			l[1] = y+1;
		}
	}
	if (x+1<row && y-1>=0 && visited[x+1][y-1] == 0)
	{
		if(map[x+1][y-1] <= c && ABS(map[x+1][y-1] - c) <= H && min > map[x+1][y-1])
		{
			min = map[x+1][y-1];
			l[0] = x+1;
			l[1] = y-1;
		}
	}
	if (x+1<row && y+1<col && visited[x+1][y+1] == 0)
	{
		if(map[x+1][y+1] <= c && ABS(map[x+1][y+1] - c) <= H && min > map[x+1][y+1])
		{
			min = map[x+1][y+1];
			l[0] = x+1;
			l[1] = y+1;
		}
	}
	if (x-1>=0 && y-1>=0 && visited[x-1][y-1] == 0)
	{
		if(map[x-1][y-1] <= c && ABS(map[x-1][y-1] - c) <= H && min > map[x-1][y-1])
		{
			min = map[x-1][y-1];
			l[0] = x-1;
			l[1] = y-1;
		}
	}
	if (x-1>=0 && y+1<col && visited[x-1][y+1] == 0)
	{
		if(map[x-1][y+1] <= c && ABS(map[x-1][y+1] - c) <= H && min > map[x-1][y+1])
		{
			min = map[x-1][y+1];
			l[0] = x-1;
			l[1] = y+1;
		}
	}
	if (min == 26)
		return 0;
	else
		return 1;
}

int go_home(int map[][10],int x, int y)
{
	int l[2];
	int diff;
	visited[x][y] = 1;
	if (x < 0 || y < 0 || x >= row || y >= col || t > T) return 0;
	if (x == 0 && y == 0) return 1;
	if (back_index(map,x,y,l)==1)
	{
		diff = map[x][y] - map[l[0]][l[1]];
		if (diff != 0)
		{
			t += 1;
			backup += 1;
		}
		if(go_home(map,l[0],l[1])==1) return 1;
	}
	return 0;
}

void find(int map[][10] ,int x, int y)
{
	int l[2];
	int diff;
	int time;
	visited[x][y] = 1;
	if (x < 0 || y < 0 || x >= row || y >= col || t > T) 
	{	
		try--;
		return ;
	}
	if(go_index(map,x,y,l)==1)
	{
		save[try%100].x = l[0]; save[try%100].y = l[1];
		diff = map[l[0]][l[1]] - map[x][y];
		time = diff * diff;
		save[try%100].time = time;
		t += time;
		try++;
		find(map,l[0],l[1]);
	}
	else
	{	
		try--;
		return ;
	}
}

int main()
{
	int map[10][10];
	int i,j;
	char buf[1024];

	while (scanf("%d %d %d %d",&row,&col,&H,&T)!=EOF)
	{
		getchar();
		for (i=0;i<row;i++)
		{
			fgets(buf,1024,stdin);
			for (j=0;j<col;j++)
				map[i][j] = buf[j]-'A';
		}
		try = 0;
		t = 0;
		init_visit();
		find(map,0,0);
		while (try>0)
		{
			backup = 0;
			init_visit();
			if(go_home(map,save[try%100].x,save[try%100].y)==1) break;
			t -= save[try%100].time;
			t -= backup;
			try--;
		}
		printf("%d\n",map[save[try%100].x][save[try%100].y]);
	}
}