#include <stdio.h> 

int size;
int start;
int answer[100];
int success, // 성공 여부 판단 
    v[10], // 지나간 간선을 저장할 스택 
    r; // 통과한 간선의 수 

int map[11][11];


void add(int s, int e)
{
	map[s][e] = 1;
	map[e][s] = 1;
}

void visit(int i) 
{ 
    int k; 
    v[r]=i;

    if(r==0 && i==start) 
    {
		answer[success] = 0; 
        for(k=0;k<=size;k++)
			answer[success] = answer[success] * 10 + v[k];
		success++;
    } 
    else 
    {
        for(k=1;k<=size;k++) 
        { 
            if(map[i][k]!=0) // 간선 존재 여부 판단 
            { 
                map[i][k]--;    map[k][i]--;  
                r--;
                visit(k); 
                map[i][k]++;    map[k][i]++; 
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

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort()
{
	int i,j,min;
	for (i=0;i<success;i++)
	{
		min = i;
		for (j=i+1;j<success;j++)
			if(answer[min]>answer[j]) min = j;
		swap(&answer[min],&answer[i]);
	}
}

void print_answer()
{
	char buf[10];
	char inv[10];
	int i,j,k;
	for(i=0;i<success;i++)
	{
		j = 0;
		while(answer[i]>0)
		{
			buf[j++] = answer[i] % 10 + 48;
			answer[i] = answer[i] / 10;
		}
		j--;
		k = 0;
		while(j>=0)
		{
			if (k%2!=0)
				inv[k++] = ' ';
			else
				inv[k++] = buf[j--];
		}
		inv[k] = '\0';
		printf("%s\n",inv);
	}
}

int main() 
{ 
	int n,a,b;
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
    	visit(start); 
    	if(success==0)
        	printf("0\n");
		else
		{
			sort();
			print_answer();
		}
	}
} 