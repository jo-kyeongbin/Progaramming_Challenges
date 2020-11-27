#include <stdio.h>

int main()
{	
	int fib[10] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}; //fib(10)까지의 원소 저장
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
			for(i=9;i>=0;i--) //큰 수부터 찾기 위해 역순으로 for문을 돌렸다.
			{
				if (value >= fib[i]) //큰 수부터 value와 같거나 작은 수를 찾아서
				{
					value = value - fib[i]; //빼주고
					result[j++] = fib[i]; //저장해준다.
				}
				if (value == 0) //종료 조건
					break;
			}
			answer = 0;
			for(i=0;i<j;i++)
				answer = answer + (result[i] * result[i]); //각 숫자들을 제곱한 수를 더한 값을 저장해준다.
			printf("%d\n",answer);
		}
	}
}