#include <stdio.h>

int vaildation(char *text, char *s)
{
	int i;
	int key;
	while (*s != '\n')
	{
		key = 0;
		for(i=0;i<6;i++)
		{
			if (*s == text[i] || *s == ' ')
			{
				key = 1;
				break;
			}
		}
		if (key == 0)
			break;
		s++;
	}
	if (*s == '\n')
		return (1);
	else
		return (-1);
}

int convert_index(char a, char *text)
{
	int i;
	for (i=0;i<6;i++)
	{
		if (text[i] == a)
			return i;
	}
	return 0;
}

void upper(char *s)
{
	int i = 0;
	while(s[i] != '\n')
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
}

int main()
{
	char text[8];
	char map_buf[38];
	char map[6][6];
	char buf[102];
	char result[100];
	int i,j,k,p;

	while (fgets(text,8,stdin)!=NULL)
	{
		upper(text);
		fgets(map_buf, 38, stdin);
		k = 0;
		for(i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				map[i][j] = map_buf[k++];
			}
		}
		while(fgets(buf,102,stdin)!=NULL)
		{
			upper(buf);
			if((vaildation(text,buf) == -1))
			{
				printf("-ERROR-\n");
				continue;
			}
			i = 0;
			p = 0;
			while(buf[i] != '\n')
			{
				if (buf[i] == ' ')
				{
					result[p++] = ' ';
					i++;
					continue;
				}
				if ((buf[i] >= 'A' && buf[i] <= 'Z'))
				{
					if((buf[i+1] >= 'A' && buf[i+1] <= 'Z'))
					{
						j = convert_index(buf[i++], text);
						k = convert_index(buf[i++], text);
						result[p++] = map[j][k];
					}
					else
					{
						printf("-ERROR-\n");
						k = -3;
						break;
					}
				}
			}
			if (k != -3)
			{
				result[p] = '\0';
				printf("%s\n",result);
			}
		}
	}
}