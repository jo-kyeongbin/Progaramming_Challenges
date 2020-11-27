#include <stdio.h>

int main()
{	
	int fib[10] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
	int testCase;
	int value;
	int result[10];
	int i,j;
	int answer;

	while(scanf("%d",&testCase)!=EOF)
	{
		getchar();
		while((testCase--)>0)
		{
			scanf("%d",&value);
			getchar();
			j = 0;
			for(i=9;i>=0;i--)
			{
				if (value >= fib[i])
				{
					value = value - fib[i];
					result[j++] = fib[i];
				}
				if (value == 0)
					break;
			}
			answer = 0;
			for(i=0;i<j;i++)
				answer = answer + (result[i] * result[i]);
			printf("%d\n",answer);
		}
	}
}