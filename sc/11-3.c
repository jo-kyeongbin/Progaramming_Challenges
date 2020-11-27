#include <stdio.h> 

int size;
int start;
int success,
    v[10];
int visited[11];

int map[11][11];


void add(int s, int e)
{
	map[s][e] = 1;
	map[e][s] = 1;
}

void visit(int i, int r) 
{ 
    int k; 

    if(r==0 && i==start) 
    {
		v[r]=i;
        for(k=size;k>0;k--)
			printf("%d ",v[k]);
		printf("%d\n",v[k]);
		success=1;
    }
    else if(r>0)
    {
        for(k=1;k<=size;k++)
        { 
            if(map[i][k]==1 && visited[i]==0)
            {
				v[r]=i;
				visited[i] = 1;
                map[i][k]=0;    map[k][i]=0;
                r--;
                visit(k,r);
				visited[i] = 0;
				map[i][k]=1;    map[k][i]=1;
				r++;
            }
        }
    }
} 

void map_init()
{
	int i,j;
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
			map[i][j] = 0;
	}
}


int main() 
{ 
	int n,a,b;
	int r;
	while(scanf("%d %d %d",&size,&n,&start)!=EOF)
	{
		getchar();
		map_init();
		while(n>0)
		{
			scanf("%d %d",&a,&b);
			getchar();
			add(a,b);
			n--;
		}
		success=0; r=size;
		for (n=0;n<11;n++)
			visited[n] = 0;
    	visit(start,r);
    	if(success==0)
        	printf("0\n");
	}
} 