#include <stdio.h>

int n;
int map[10][10];
int key;

const int EXIST = -1;
const int NONE = 0;

void print_map()
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
}

int exist(void)
{
	int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(map[i][j] == EXIST)
				return 1;
	}
	return 0;
}

int find(int i, int j, int value)
{
	if(i<0 || j<0 || i>=n || j>=n) {
    	return 0;
    }
	else if(exist() == 0){
		print_map();
        return 1;
    }
	else if (map[i][j] < value && map[i][j] >= 0 && key != 1)
	{
		key = 0;
		while(i<n)
		{
			while(j<n)
			{
				if(map[i][j] < value && map[i][j] >= 0)
					j++;
				if(map[i][j] == EXIST)
				{
					key = 1;
					break;
				}
			}
			if (key == 1)
				break;
			i++;
			j=0;
		}
	}
	if(map[i][j] == EXIST){
		key = 1;
		map[i][j] = value;
        if(find(i, j+1,value) || find(i+1, j,value)
		|| find(i, j-1, value) || find(i-1,j,value)) {
			return 1;
    	}
    }
	return 0;
}

int main()
{
	int i,j,k;
	char buf[1024];
	while(scanf("%d",&n)!=EOF)
	{
		getchar();
		for(i=0;i<n;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<n;j++)
			{
				map[i][j] = buf[k]-'0';
				if (map[i][j] == 1)
					map[i][j] = -1;
				k+=2;
			}
		}
		i = 1;
		while (exist()!=0)
		{
   			key = 0;
			find(0,0,i);
			i++;
		}
	}
}
