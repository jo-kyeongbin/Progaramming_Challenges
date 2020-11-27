#include <stdio.h>
//카탈란 수 알고리즘을 이용하여 해결 b가 ( 이고 c가 )로 생각하면 문제이해에 도움이 된다.
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
	if (b == 0 && c == 0) //출력조건
	{
		buf[n]=0;
		printf("%s\n",buf);
		return;
	}
	if (b > 0) //b if문이 더 먼저 있어서 box를 우선시 출력.
	{
		buf[n] = 'b';
		solution(buf, n+1, b-1, c+1);
	}
	if (c > 0) //dfs 방식으로 위에서 출력조건이 만족되어 출력된 후 바로 직전부터 c로 채우면서 접근.
	{
		buf[n] = 'c';
		solution(buf,n+1,b,c-1);
	}
}