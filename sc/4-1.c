#include <stdio.h>

int len(char *s) //문자열의 길이를 측정해주는 함수
{
	int i = 0;
	while(s[i])
		i++;
	if (s[i-1] == '\n') //개행을 받아들이는 fgets일경우 크기는 i-1
		return (i-1);
	else 
	{
		return (i);
	}
	
}

int	iter(char *str, char c) //문자열 str에서 문자 c가 발견되면 '0'으로 바꾸고 리턴 1을 해준다.
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == c)
		{
			str[i - 1] = '0';
			return (1);
		}
	return (0);
}

int	main()
{
	char buf1[1002];
	char buf2[1002];
	int i = 0;
	int count = 0;
	while (fgets(buf1,1002,stdin)!=NULL)
	{
		fgets(buf2,1002,stdin);
		while (buf1[i]!='\n')
		{
			if (iter(buf2, buf1[i])) //만약에 buf2에 문자 buf[i]가 있다면 count 증가
				count++;
			i++;
		}
		printf("%d\n",len(buf1) + len(buf2) - (count*2)); //count는 두 문자열 사이에 공통으로 존재하는 문자의 개수이므로, 문제에서 요구하는 문자에서 지워야할 최소 개수는 다음과 같다.
	}
}