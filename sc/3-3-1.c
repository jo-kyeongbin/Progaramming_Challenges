#include <stdio.h>
#include <stdlib.h>

void reverse(int *size, int count)
{
	int i;
	int temp[count];
	for(i=0;i<count;i++)
		temp[i] = size[count -1 -i];
	for(i=0;i<count;i++)
		size[i] = temp[i];
}

int get_length(char *s)
{
	int i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return i;
}

int my_atoi(char *buf)
{
	int i;
	int length = get_length(buf);
	int result;
	result = buf[0] - '0';
	for(i=1;i<length - 1;i++)
		result = (result * 10) + (buf[i] - '0');
	return result;
}

int main()
{
	char *buf;
	int temp;
	char *op;
	int *result;
	int size[1000];
	char count_buf[6];
	int count, i, k, index, key;
	while(fgets(count_buf,6,stdin)!=NULL){
	count = my_atoi(count_buf);
	if (!(count >= 0 && count <= 1000))
	{
		printf("Wrong Command!\n");
		continue;
	}
	buf = (char *)malloc(sizeof(char)*2048);
	scanf("%[^\n]s",buf);
	getchar();
	if(count == 0 && buf[0])
	{
		printf("Wrong Command!\n");
		continue;
	}
	i=0;
	temp = 0;
	k = 0;
	key = 0;
	while (buf[i] && key == 0)
	{
		while (buf[i] != ' ' && buf[i])
		{
			if (temp == 0)
				temp = buf[i] - '0';
			if ((buf[i] >= '0' && buf[i] <= '9') && (buf[i+1] >= '0' && buf[i+1] <= '9'))
				temp = (temp * 10) + (buf[i + 1] - '0');
			i++;
		}
		if (k < count)
		{
			if (temp >= 1 && temp <= 1000000)
				size[k++] = temp;
			else
			{
				printf("Wrong Command!\n");
				key = 1;
			}
		}
		temp = 0;
		if (buf[i])
			i++;
	}
	op = (char *)malloc(sizeof(char)*100000);
	scanf("%s",op);
	getchar();
	i = 0;
	while (op[i] && key == 0)
	{
		switch(op[i])
		{
			case 'R':
				index = 0;
				while (index < count)
				{
					if(size[index] > 0)
						break;
					index++;
				}
				if (index == count && size[index] == 0)
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				reverse(size,count);
				break;
			case 'S':
				index = 0;
				while (index < count)
				{
					if(size[index] > 0)
						break;
					index++;
				}
				if (index == count && size[index] == 0)
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				if (index + 1 < count)
				{
					for(k=index + 1;k<count;k++)
					{
						if(size[k]<size[index] && size[k] != 0)
							index = k;
					}
				}
				if (size[index] != 0)
					size[index] = 0;
				break;
			case 'B':
				index = 0;
				while (index < count)
				{
					if(size[index] > 0)
						break;
					index++;
				}
				if (index == count && size[index] == 0)
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				if (index + 1 < count)
				{
					for(k=index + 1;k<count;k++)
					{
						if(size[k]>size[index] && size[k] != 0)
							index = k;
					}
				}
				if (size[index] != 0)
					size[index] = 0;
				break;
			default:
				printf("Wrong Command!\n");
				key = 1;
		}
		i++;
	}
	k = 0;
	result = (int *)malloc(sizeof(int)*1024);
	for (i=0;i<count;i++)
	{
		if (size[i] > 0)
			result[k++] = size[i];
	}
	if (k == 0 && key == 0)
		printf("Empty!\n");
	if (key == 0 && result[0] != '\0')
	{
		for(i=0;i<k;i++)
		{
			if (i != k - 1)
				printf("%d ",result[i]);
			else
				printf("%d\n", result[i]);
		}
	}
	free(result);
	free(op);
	free(buf);
	}
}