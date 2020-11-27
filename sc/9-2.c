#include <stdio.h>

char answer[11];
char correct[11];
char temp[11];
char buf[1024];
int count;
int N;

int my_strcmp(char *s1, char *s2) //두 문자열을 비교해주는 함수, 완전히 같으면 return 1 하나라도 다르면 return 0
{
	int i=0,j=0;
	while(s1[i] && s2[j])
	{
		if (s1[i] == s2[j])
		{	
			i++;
			j++;
		}
		else
			return 0;
	}
	return 1;
}

void my_strcpy(char *s1, char *s2) //문자열 s1에 문자열 s2의 내용을 복사하고 널을 붙인다.
{
	int i=0;
	while(s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

void find(int pos)
{
	int i;
	if (pos==N) //재귀함수 호출이 종료되는 부분, pos가 입력값의 길이가 되었을 경우.
	{
		for(i=0;i<N;i++) //answer를 문제에서 요구하는 순열대로 구현하여 temp에 저장한다. 즉 answer는 이전 상태.
		{
			if (i==0) //처음부분(처음부분과 끝부분은 연결되어 있으므로 따로 분리하여 처리)
			{
				if (answer[N-1] == answer[1])
					temp[i] = answer[i];
				else
				{
					if (answer[i] == '0')
						temp[i] = '1';
					else
						temp[i] = '0';
				}
			}
			else if(i==N-1) //끝부분
			{
				if (answer[N-2] == answer[0])
					temp[i] = answer[i];
				else
				{
					if (answer[i] == '0')
						temp[i] = '1';
					else
						temp[i] = '0';
				}
			}
			else // 그 외 중간부분
			{
				if (answer[i-1] == answer[i+1])
					temp[i] = answer[i];
				else
				{
					if (answer[i] == '0')
						temp[i] = '1';
					else
						temp[i] = '0';
				}
			}
		}
		answer[N] = '\0';
		temp[N] = '\0';
		if(my_strcmp(temp,buf)==1) //입력값과 temp가 같다면
		{
			count++; //정답 횟수 증가
			my_strcpy(correct,answer); //정답을 따로 저장한다.
		}
	}
	else{ //해당 length를 충족하는 모든 경우의 수를 순회
		answer[pos] = '0'; //해당 부분이 0일 때 재귀호출
		find(pos+1);
		answer[pos] = '1'; //해당 부분이 1일 때 재귀호출
		find(pos+1);
	}
}

int my_strlen(char *buf) //문자열의 길이를 측정하는 함수
{
	int i = 0;
	while(buf[i]!='\n' && buf[i])
		i++;
	return(i);
}

int main()
{
	while(fgets(buf,1024,stdin)!=NULL)
	{
		N = my_strlen(buf);
		buf[N] = '\0';
		count = 0;
		find(0);
		if (count == 1) //이전 상태가 하나일 경우 답을 출력
			printf("%s\n",correct);
		else if(count > 1) //이전 상태가 여러개면 multiple
			printf("multiple\n");
		else //이전 상태가 존재하지 않으면 zero
			printf("zero\n");
	}
}