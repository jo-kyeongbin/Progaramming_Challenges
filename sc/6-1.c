#include <stdio.h>

typedef struct product{
	char name[21]; //상품명
	int day; //일
	int month; //월
	int year; //년
	int total; //년월일을 합친 정수
}product;

int my_atoi(char *a) //문자열을 정수로 변환시켜주는 함수
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
	char y[5]; //년도
	char m[3]; //월
	char d[3]; //일
	char name[21]; //상품명
	char num[9]; //년도+월+일을 합치기 위한 문자열

	int ymd; //년월일을 합쳐놓은 정수
	int day = 0; //일(인덱스역할, 변수역할)
	int month = 0;//월(인덱스, 변수)
	int year = 0;//년도(인덱스, 변수)
	int r = 0;
	int i = 0;
	int cheak = 0; // '/'를 기준으로 나누기 위한 변수

	while(value[i]!='\n' && value[i])
	{
		if ((value[i] >= 'a' && value[i] <= 'z') || value[i] == ' ') //상품명
			name[r++] =value[i++];
		else
		{
			if (value[i] != '/' && cheak == 0)//일, /를 만날때마다 cheak++
				d[day++]=value[i];
			if (value[i] != '/' && cheak == 1)//월
				m[month++]=value[i];
			if (value[i] != '/' && cheak == 2)//년도
				y[year++]=value[i];
			if (value[i] == '/')
				cheak++;
			i++;
		}
	}
	//문자열을 처리하기 위한 널문자 추가
	d[day] = '\0';
	m[month] = '\0';
	y[year] = '\0';
	name[r] = '\0';
	
	i = 0;
	r = 0;
	//num은 년도, 월, 일 순서로 합쳐주기 위한 문자열
	while(y[r])
		num[i++] = y[r++];
	r = 0;
	while(m[r])
		num[i++] = m[r++];
	r = 0;
	while(d[r])
		num[i++] = d[r++];
	num[i] = '\0';
	//정수로 변환
	ymd = my_atoi(num);
	day = my_atoi(d);
	month = my_atoi(m);
	year = my_atoi(y);
	i = 0;
	if (!(year < 2017 || (year == 2017 && month < 10) || (year == 2017 && month == 10 && day < 19)))
	{ //유통기한이 지나지 않았다면
		while(name[i]) //정보추가
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


void swap(int *a, int *b) //순서를 바꿔주는 함수
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_period(product *list, int *index, int count) //유통기한 순으로 정렬해주는 함수
{
	int i, j;
	int min;
	for(i=0;i<count;i++) //선택정렬 활용
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].total < list[index[min]].total) min = j;
		swap(&index[i], &index[min]);
	}
}

int my_strcpy(char *a, char *b) //두 문자의 아스키코드를 비교해주는 함수
{
	if (!*a || !*b)
		return -2;
	while(*a)
	{
		if(*a > *b || !(*b)) //a가 더 크거나, b의 길이보다 a의 길이가 더 길 경우 리턴 1
			return 1;
		if(*a < *b) //b가 더 크다면 -1
			return -1;
		a++;
		b++;
	}
	if(*a == *b) //두 문자열이 동일하다면 리턴 0
		return 0;
	if(*b) //b가 더 크다면 -1
		return -1;
	return 0;
}

void sort_name(product *list, int *index, int count) //이름순으로 정렬시켜주는 함수
{
	int i, j;
	int min;
	for(i=0;i<count;i++) //선택정렬 활용
	{
		min = i;
		for(j=i+1;j<count;j++) //index[min]을 가진 list보다 더 작으면 min값 업데이트
			if(my_strcpy(list[index[j]].name, list[index[min]].name) == -1 || 
			((my_strcpy(list[index[j]].name, list[index[min]].name) == 0) && list[index[j]].total < list[index[min]].total)) min = j; //이름이 같으면 년도 순으로 정렬
		swap(&index[i], &index[min]);
	}
}

void print_list(product *list, int *index, int count) //유효한 상품 리스트의 정보들을 출력해주는 함수
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
		count = my_atoi(buf); //scanf로 바로 받아와도 된다.
		for(i=0;i<count;i++)
		{
			fgets(buf2[count],1024,stdin);
			init_product(buf2[count],&list[i]); //상품의 정보를 기입
		}
		for(i=0;i<count;i++)
			index[i] = i;
		
		sort_period(list, index, count); //기한 순으로 정렬 후
		sort_name(list,index,count); //이름 순으로 정렬
		print_list(list,index,count); //출력
	}
}