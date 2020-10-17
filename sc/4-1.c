#include <stdio.h>

int len(char *s)
{
	int i = 0;
	while(s[i])
		i++;
	if (s[i-1] == '\n')
		return (i-1);
	else
	{
		return (i);
	}
	
}

int	iter(char *str, char c)
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
			if (iter(buf2, buf1[i]))
				count++;
			i++;
		}
		printf("%d\n",len(buf1) + len(buf2) - (count*2));
	}
}