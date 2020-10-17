#include <stdio.h>
#define ABS(x) (((x)<0)?-(x):(x))

typedef struct position{
	int x;
	int y;
	int diff;
}position;

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_x(int *index, position *list, int count)
{
	int i,j,min;

	for (i=0;i<count;i++)
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].x < list[index[min]].x) min = j;
		swap(&index[i], &index[min]);
	}
}

void sort_y(int *index, position *list, int count)
{
	int i,j,min;

	for (i=0;i<count;i++)
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].y < list[index[min]].y) min = j;
		swap(&index[i], &index[min]);
	}
}

int main()
{
	int count, result, i, k;
	int gap[1000];
	int mid, min, x, y;
	int sum;
	char buf[1024];
	position list[1000];
	int index[1000];

	while(scanf("%d %d",&count, &result)!=EOF)
	{
		getchar();
		sum = 0;
		mid = (count-1) / 2;
		for(i=0;i<count;i++)
		{
			fgets(buf,1024,stdin);
			list[i].x = buf[0]-'0';
			list[i].y = buf[2]-'0';
		}
		for(i=0;i<count;i++)
			index[i] = i;
		sort_x(index, list, count);
		x = list[index[mid]].x;
		for(i=0;i<count;i++)
			index[i] = i;
		sort_y(index,list,count);
		y = list[index[mid]].y;
		for(i=0;i<count;i++)
		{
			list[i].diff = ABS(list[i].x - x) + ABS(list[i].y - y);
			sum += list[i].diff;
			gap[k++] = list[i].diff;
		}
		printf("%d\n",sum);
		for(i=0;i<count;i++)
			index[i] = i;
		for(i=0;i<result;i++)
		{
			min = 0;
			for(k=0;k<count;k++)
				if(gap[k] < gap[min]) min = k;
			printf("%d %d\n",list[min].x, list[min].y);
			gap[min] = 9999;
		}
	}
}