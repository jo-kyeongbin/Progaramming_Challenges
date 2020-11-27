#include <stdio.h>

int n, count;
int map[10][10];
int x[100], y[100], l[100];


void save(int i, int j, int k)
{ 
	x[count] = i; 
	y[count] = j; 
	l[count] = k; 
	count++; 
}


void bfs(int i, int j)
{
	int pos = 0;
	save(i, j, 1);

	while (pos < count && (x[pos] != n - 1 || y[pos] != n - 1))
	{
		map[y[pos]][x[pos]] = 0;
		if (y[pos] > 0 && map[y[pos] - 1][x[pos]] == 1)
			save(x[pos], y[pos] - 1, l[pos] + 1);
		if (y[pos] < n - 1 && map[y[pos] + 1][x[pos]] == 1)
			save(x[pos], y[pos] + 1, l[pos] + 1);
		if (x[pos] > 0 && map[y[pos]][x[pos] - 1] == 1)
			save(x[pos] - 1, y[pos], l[pos] + 1);
		if (x[pos] < n - 1 && map[y[pos]][x[pos] + 1] == 1)
			save(x[pos] + 1, y[pos], l[pos] + 1);
		pos++;
	}
	if (pos < count) 
		printf("%d\n", l[pos]);
}

int main()
{
	int i,j,k,row,col;
	char buf[1024];
	while(scanf("%d",&n)!=EOF)
	{
		getchar();
		row = n;
		col = n;
		for(i=0;i<row;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<col;j++)
			{
				map[i][j] = buf[k]-'0';
				k+=2;
			}
		}
   		bfs(0,0);
	}
	return 0;
}
