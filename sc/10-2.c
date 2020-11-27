#include <stdio.h>

void solution(char *buf,int n, int b, int c);

int main()
{
	int n;
	int i;
	char buf[25];
	while(scanf("%d",&n)!=EOF)
	{
		solution(buf,0,n,0);
	}
}

void solution(char *buf,int n, int b, int c)
{
	if (b == 0 && c == 0)
	{
		buf[n]=0;
		printf("%s\n",buf);
		return;
	}
	if (b > 0)
	{
		buf[n] = 'b';
		solution(buf, n+1, b-1, c+1);
	}
	if (c > 0)
	{
		buf[n] = 'c';
		solution(buf,n+1,b,c-1);
	}
}