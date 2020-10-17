#include <stdio.h>

typedef struct product{
	char name[21];
	int day;
	int month;
	int year;
	int total;
}product;

int my_atoi(char *a)
{
	int result = 0;
	while (*a!='\n' && *a)
	{
		result = (result * 10) + (*a - '0');
		a++;
	}
	return result;
}


void init_product(char *value, product *list)
{
	char y[5];
	char m[3];
	char d[3];
	char name[21];
	char num[9];

	int ymd;
	int day = 0;
	int month = 0;
	int year = 0;
	int r = 0;
	int i = 0;
	int cheak = 0;

	while(value[i]!='\n' && value[i])
	{
		if ((value[i] >= 'a' && value[i] <= 'z') || value[i] == ' ')
			name[r++] =value[i++];
		else
		{
			if (value[i] != '/' && cheak == 0)
				d[day++]=value[i];
			if (value[i] != '/' && cheak == 1)
				m[month++]=value[i];
			if (value[i] != '/' && cheak == 2)
				y[year++]=value[i];
			if (value[i] == '/')
				cheak++;
			i++;
		}
	}
	
	d[day] = '\0';
	m[month] = '\0';
	y[year] = '\0';
	name[r] = '\0';
	
	i = 0;
	r = 0;
	while(y[r])
		num[i++] = y[r++];
	r = 0;
	while(m[r])
		num[i++] = m[r++];
	r = 0;
	while(d[r])
		num[i++] = d[r++];
	num[i] = '\0';

	ymd = my_atoi(num);
	day = my_atoi(d);
	month = my_atoi(m);
	year = my_atoi(y);
	i = 0;
	if (!(year < 2017 || (year == 2017 && month < 10) || (year == 2017 && month == 10 && day < 19)))
	{
		while(name[i])
		{
			(*list).name[i] = name[i];
			i++;
		}
		(*list).name[i]='\0';
		(*list).year = year;
		(*list).month = month;
		(*list).day = day;
		(*list).total = ymd;
	}
}


void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_period(product *list, int *index, int count)
{
	int i, j;
	int min;
	for(i=0;i<count;i++)
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].total < list[index[min]].total) min = j;
		swap(&index[i], &index[min]);
	}
}

int my_strcpy(char *a, char *b)
{
	if (!*a || !*b)
		return -2;
	while(*a)
	{
		if(*a > *b || !(*b))
			return 1;
		if(*a < *b)
			return -1;
		a++;
		b++;
	}
	if(*a == *b)
		return 0;
	if(*b)
		return -1;
	return 0;
}

void sort_name(product *list, int *index, int count)
{
	int i, j;
	int min;
	for(i=0;i<count;i++)
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(my_strcpy(list[index[j]].name, list[index[min]].name) == -1 || 
			((my_strcpy(list[index[j]].name, list[index[min]].name) == 0) && list[index[j]].total < list[index[min]].total)) min = j;
		swap(&index[i], &index[min]);
	}
}

void print_list(product *list, int *index, int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		if (list[index[i]].total != 0)
			printf("%s%d/%d/%d\n",list[index[i]].name, list[index[i]].day, list[index[i]].month, list[index[i]].year);
	}
}

int main()
{
	char buf[1024];
	int count;
	int i;
	char buf2[100][1024];
	int index[100];
	product list[100];

	while (fgets(buf,1024,stdin)!=NULL)
	{
		count = my_atoi(buf);
		for(i=0;i<count;i++)
		{
			fgets(buf2[count],1024,stdin);
			init_product(buf2[count],&list[i]);
		}
		for(i=0;i<count;i++)
			index[i] = i;
		
		sort_period(list, index, count);
		sort_name(list,index,count);
		print_list(list,index,count);
	}
}