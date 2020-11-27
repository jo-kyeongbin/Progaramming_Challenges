#include <stdio.h>

char answer[11];
char correct[11];
char temp[11];
char buf[1024];
int count;
int N;

int my_strcmp(char *s1, char *s2)
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

void my_strcpy(char *s1, char *s2)
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
	if (pos==N)
	{
		for(i=0;i<N;i++)
		{
			if (i==0)
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
			else if(i==N-1)
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
			else
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
		if(my_strcmp(temp,buf)==1)
		{
			count++;
			my_strcpy(correct,answer);
		}
	}
	else{
		answer[pos] = '0';
		find(pos+1);
		answer[pos] = '1';
		find(pos+1);
	}
}

int my_strlen(char *buf)
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
		if (count == 1)
			printf("%s\n",correct);
		else if(count > 1)
			printf("multiple\n");
		else
			printf("zero\n");
	}
}