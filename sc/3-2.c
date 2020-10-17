#include <stdio.h>

int main(){
	int tables, i, k, min_index, key;
	char buf[1024];

	scanf("%d",&tables);
	getchar();
	char exist[tables];
	for(i=0;i<tables;i++)
		exist[i] = '#';
	scanf("%[^\n]s",buf);
	i = 0;
	min_index = 0;
	while (buf[i])
	{
		if ('A'<=buf[i] && 'Z'>=buf[i])
		{
			for (k = 0;k < tables;k++)
			{
				if (exist[k] == '#')
				{
					exist[k] = buf[i];
					break;
				}
			}
			i++;
			continue;
		}
		if (buf[i] == '*')
		{
			key = 0;
			for (k=0; k<tables; k++)
			{
				if (exist[k] != '#' && key == 0)
				{	
					min_index = k;
					key = 1;
				}
				if (exist[k] != '#' && exist[min_index] > exist[k])
				{
					min_index = k;
				}
			}
			exist[min_index] = '#';
			i++;
			continue;
		}
		i++;
	}
	for (k=0;k<tables;k++)
	{
		if (k != tables - 1)
			printf("%c ",exist[k]);
		else
			printf("%c\n",exist[k]);
			
	}
}
