#include <stdio.h>

int row, col;
int map[10][10];

const int PATHWAY = 1;
const int BLOCKED = 4;
const int PATH = 3;
const int DST = 2;

void print_map()
{
	int i,j,count;
	count = 0;
	for (i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if (map[i][j]==PATH)
			{
				printf("1 ");
				count++;
			}
			else if(map[i][j] == DST)
			{
				printf("%d ",DST);
				count++;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("%d\n",count);
}


int find(int i, int j)
{
	if(i<0 || j<0 || i>=row || j>=col) {
    	return 0;
    }else if(map[i][j] != PATHWAY && map[i][j] != 2) return 0;
    else if(map[i][j]==DST) {
		printf("\n");
		print_map();
        return 0;
    }else {
        map[i][j] = PATH;
        if(find(i, j+1) || find(i+1, j)
            || find(i, j-1) || find(i-1, j)) {
			return 1;
    }
	if (map[i][j]==PATH)
		map[i][j] = PATHWAY;
	else
		map[i][j] = BLOCKED;
    return 0;
    }
}

int main()
{
	int i,j,k;
	char buf[1024];
	while(scanf("%d %d",&row,&col)!=EOF)
	{
		getchar();
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
   		find(0,0);
	}
}
