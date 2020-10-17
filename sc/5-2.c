#include <stdio.h>

void remove_same_word(char *result, int *index)
{
	int i=0,j=0;
	int k,l;
	char answer[1024];
	while(index[i]!=-1)
	{
		j = i + 1;
		while(index[j]!=-1)
		{
			k = index[i];
			l = index[j];
			while (result[k]==result[l] && result[k] != ' ')
			{
				k++;
				l++;
			}
			if (result[k] == ' ' && result[l] == ' ' && (result[k-1] == result[l-1]))
			{
				for(i=0;i<index[j]-1;i++)
					answer[i] = result[i];
				answer[i++] = ' ';
				answer[i]= '\0';
				printf("%s\n",answer);
				return;
			}
			j++;
		}
		i++;
	}
	printf("%s\n",result);
}

int main()
{
	char buf[1024];
	char result[1024];
	int index[11];
	int i, j, k, key;
	while(fgets(buf,1024,stdin)!=NULL)
	{
		for(i=0;i<11;i++)
			index[i] = -1;
		i = 0;
		j = 0;
		k = 0;
		key = 1;
		while(buf[i]!='\n' && key == 1 && buf[i])
		{
			if(buf[i]>='0' && buf[i]<='9')
			{
				i++;
				continue;
			}
			if(buf[i]==' ')
			{
				if(!(buf[i-1]>='0' && buf[i-1]<='9'))
					result[j++] = buf[i];
				i++;
				continue;
			}
			if(buf[i]>='a' && buf[i]<='z')
			{
				if(buf[i-1]==' ')
					index[k++] = j;
				result[j] = buf[i];
				if(buf[i+1]==' ')
				{
					if(buf[i+2] != buf[i])
					key = 0;
				}
				i++;
				j++;
			}
		}
		key  = 1;
		result[j++] = ' ';
		result[j] = '\0';
		remove_same_word(result,index);
	}
}