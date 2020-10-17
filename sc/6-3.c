#include <stdio.h>

typedef struct team{
	char name[22];
	int plus;
	int minor;
	int win;
	int lose;
	int plus_minor;
	int winner[10];
}team;

void cal_score(team *list, char *buf, int count)
{
	int i,score_index=0,k,s;
	int key;
	int lose_index;
	int win_index;
	
	while(!(buf[score_index]==':' && buf[score_index-1] >= '0' && buf[score_index-1] <= '9' && buf[score_index+1] >= '0' && buf[score_index+1] <= '9'))
		score_index++;
	for(i=0;i<count;i++)
	{
		k = 0;
		key = 0;
		while(list[i].name[k])
		{
			if(list[i].name[k] == buf[k])
			{
				k++;
				continue;
			}
			else
			{
				key = 1;
				break;
			}
		}
		if (key == 0)
		{
			list[i].plus+=(buf[score_index-1] -'0');
			list[i].minor+=(buf[score_index+1] -'0');
			if(buf[score_index-1] > buf[score_index+1])
			{
				list[i].win++;
				win_index = i;
			}
			else
			{
				list[i].lose++;
				lose_index = i;
			}
			break;
		}
	}
	for(i=0;i<count;i++)
	{
		s = score_index+3;
		k = 0;
		key = 0;
		while(list[i].name[k])
		{
			if(list[i].name[k] == buf[s])
			{
				s++;
				k++;
				continue;
			}
			else
			{
				key = 1;
				break;
			}
		}
		if (key == 0)
		{
			list[i].plus+=(buf[score_index+1] -'0');
			list[i].minor+=(buf[score_index-1] -'0');
			if(buf[score_index+1] > buf[score_index-1])
			{
				list[i].win++;
				win_index = i;
			}
			else
			{
				list[i].lose++;
				lose_index = i;
			}
			break;
		}
	}
	list[win_index].winner[lose_index] = 1;
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort(team *list, int *index, int count)
{
	int i,j,max;
	for(i=0;i<count;i++)
	{
		max = i;
		for(j=i+1;j<count;j++)
		{
			if((list[index[j]].win > list[index[max]].win) ||
			((list[index[j]].win == list[index[max]].win) && (list[index[j]].plus_minor > list[index[max]].plus_minor)) ||
			((list[index[j]].win == list[index[max]].win) && (list[index[j]].plus_minor == list[index[max]].plus_minor) && (list[index[j]].winner[index[max]] == 1)))
				max = j;
		}
		swap(&index[i], &index[max]);
	}
}

void init_list(team *list, int count)
{
	int i,j;
	for(i=0;i<count;i++)
	{
		list[i].win = 0;
		list[i].lose = 0;
		list[i].plus = 0;
		list[i].minor = 0;
		for(j=0;j<10;j++)
			list[i].winner[j] = 0;
	}
}

int main()
{
	team list[10];
	char buf[1024];
	int index[10];
	int count, i, k, match;

	while(scanf("%d",&count)!=EOF)
	{
		getchar();
		for(i=0;i<count;i++)
		{
			fgets(list[i].name,22,stdin);
			k = 0;
			while(list[i].name[k] != '\n')
				k++;
			list[i].name[k] = '\0';
		}
		init_list(list,count);
		match = (count)*(count-1)/2;
		for(i=0;i<match;i++)
		{
			fgets(buf,1024,stdin);
			cal_score(list, buf, count);
		}
		for(i=0;i<count;i++)
		{
			index[i] = i;
			list[i].plus_minor = list[i].plus - list[i].minor;
		}
		sort(list,index,count);
		for(i=0;i<count;i++)
		{
			k = index[i];
			printf("%d) %s %d %d %d-%d %d\n",i+1, list[k].name, list[k].win, list[k].lose, list[k].plus, list[k].minor, list[k].plus_minor);
		}
	}
}