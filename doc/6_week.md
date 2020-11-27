# 6주차-정렬

## 문제 1

### 문제설명

한 슈퍼마켓의 아르바이트생인 Teemo는 가게의 식료품들을 진열하는 업무를 맡았다.<br>
알파벳순으로 진열하며 같은 상품의 경우 유통기한(일/월/년)이 짧은 순으로 앞에 진열한다.<br>
<br>
상품의 갯수와 함께 각 상품의 식품명과 유통기한이 주어졌을 때, 앞에 진열되는 상품부터 차례대로 출력하라.<br>
상품의 갯수는 100개 이하이며, 식품명은 20자 이내의 알파벳 소문자로 구성된다.<br>
유통기한은 1990년부터 2020년 사이의 유효한 날짜이다.<br>
*단, 유통기한이 2017년 10월 19일 이전인 날짜가 지난 상품은 진열하지 않는다.<br>
<br>
### 실행 화면 예시

<img src="/img/6-1.png" width="60%" height="60%">

### 코드
```c
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
```

## 문제 2

### 문제설명

__교과서 참고: 25번__<br>
<br>
유명한 갱스터인 비토 데드스톤이 뉴욕으로 이사를 간다. 뉴욕에는 그의 가족들이 매우 많이 살고 있는데 그들은 모두 교차로 근처에 살고 있어서, 동서로는 i번가 남북으로는 j번가 같은 식으로 위치를 표현할 수 있다.<br>
뉴욕에서는 대각선 방향으로 이동하는 것이 불가능해서, 예를 들어 (0, 2)에서 (4, 5)까지 가려면 무조건 일곱 블록만큼 이동해야 한다.<br>
비토는 모든 친척집과의 이동 거리 총합이 가장 작은 곳에 집을 구하고 싶어하는데, 하필이면 당신에게 그 문제를 해결하기 위한 프로그램을 만들어내라는 협박 편지를 보내왔다.<br>
<br>
입력의 첫째 줄에는 친척집의 수 n(n<1000)과 이동거리가 작은 순서대로 구할 좌표의 수 m , 그 후 n줄에 걸쳐서 각 친척집의 x, y 좌표가 있다. (m <= n, 0 <= x, y < 10)<br>
주어진 테스트 케이스에 대하여 정답은 유일하다.<br>
<br>
비토가 원하는 위치에 집을 구했을 때, 그 집으로부터 각 친척집까지의 이동 거리의 총합을 출력하고, 비토의 집에서 이동거리가 가장 작은 곳부터 m개의 친척집의 좌표를 출력하라.<br>
만약, 이동거리가 같은 경우에는 먼저 입력받은 친척집의 좌표부터 출력한다.<br>
*(x0, y0)와 (x1, y1)사이의 이동 거리는 | x1 - x0 | + | y1 - y0 | 로 구한다.<br>
<br>
### 실행 화면 예시

<img src="/img/6-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#define ABS(x) (((x)<0)?-(x):(x)) //절대값 메크로 함수

typedef struct position{
	int x; //x좌표
	int y; //y좌표
	int diff; //비토의 이사집과의 거리차이
}position;

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_x(int *index, position *list, int count) //인덱스 배열을 x좌표에 대해서 정렬
{
	int i,j,min;

	for (i=0;i<count;i++) //선택정렬
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].x < list[index[min]].x) min = j;
		swap(&index[i], &index[min]);
	}
}

void sort_y(int *index, position *list, int count) //인덱스 배열을 y좌표에 대해서 정렬
{
	int i,j,min;

	for (i=0;i<count;i++) //선택정렬
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
	int gap[1000]; //비토의 집과의 거리차 저장 변수
	int mid, min, x, y; //mid(중앙값):비토가 이사갈 좌표, min : 출력을 위해 최소 거리차를 가진 좌표 인덱스를 저장
	int sum; //거리차들의 총합을 저장
	char buf[1024];
	position list[1000];
	int index[1000]; //원래의 정보를 유지하기 위해 인덱스 배열 활용.

	while(scanf("%d %d",&count, &result)!=EOF)
	{
		getchar();
		sum = 0;
		mid = (count-1) / 2;
		for(i=0;i<count;i++)
		{
			fgets(buf,1024,stdin);
			list[i].x = buf[0]-'0'; //x좌표, y좌표를 받아온다.
			list[i].y = buf[2]-'0';
		}
		for(i=0;i<count;i++)
			index[i] = i; //처음의 순서로 인덱스 배열 초기화
		sort_x(index, list, count); //x좌표에 대해서 정렬
		x = list[index[mid]].x; //x좌표의 중앙값이 비토가 이사갈 집의 x좌표
		for(i=0;i<count;i++)
			index[i] = i;//처음의 순서로 인덱스 배열 초기화
		sort_y(index,list,count);//y좌표에 대해서 정렬
		y = list[index[mid]].y; //y좌표의 중앙값이 비토가 이사갈 집의 y좌표
		for(i=0;i<count;i++)
		{
			list[i].diff = ABS(list[i].x - x) + ABS(list[i].y - y); //구한 비토의 좌표로부터 친척집들과의 차이를 계산하여 저장.
			sum += list[i].diff; // 차이값을 합산
			gap[k++] = list[i].diff; //차이값들을 따로 배열로 저장한다. (들어온 순서 고려)
		}
		printf("%d\n",sum); //거리차의 총합을 출력해준다.
		for(i=0;i<count;i++)
			index[i] = i;//y좌표에 대해 정렬되어 있는 인덱스를 다시 초기화 시킨다.
		for(i=0;i<result;i++)
		{
			min = 0;
			for(k=0;k<count;k++)
				if(gap[k] < gap[min]) min = k;
			printf("%d %d\n",list[min].x, list[min].y); //가장 가까운 거리 순으로 출력해준다.
			gap[min] = 9999; //이미 출력한 것은 제외하기 위해 9999로 초기화.
		}
	}
}
```

## 문제 3

### 문제설명
__<참고: 문제 32 – 축구>__<br>
<br>
게임 대회 조별리그를 진행한다. 한 조에 n(n < 10)개의 팀이 들어가 리그를 진행하며, 순위를 매긴 후 상위권의 성적을 거둔 팀들만 상위 토너먼트에 진출할 수 있다.<br>
특정 조의 팀명과 팀별 게임 결과들이 들어오면, 그것을 토대로 해당 조의 순위표를 출력해야 한다.<br>
조 안의 모든 팀들은 조 안에 있는 모든 상대와 게임을 진행하므로, 게임 수에 있어서 순위를 결정해야 하는 문제는 발생하지 않는다.<br>
<br>
조별리그의 순위 규칙은 다음과 같다.<br>
<br>
1. 무승부는 발생하지 않으며, 1차적으로는 승리한 게임 수가 높은 순서대로 순위를 결정한다.<br>
2. 승리한 게임 수가 동일하다면 세트득실점으로 순위를 구분한다.<br>
3. 세트득실점이 같다면 승자결정전 없이 승자승(두 팀간의 이전 경기에서 승리했었던 쪽을 이긴 것으로 치는 것)을 적용한다.<br>
(3개 이상의 팀이 승리한 게임 수와 세트득실이 모두 같은 경우는 없다고 가정한다.)<br>
<br>
입력으로 들어오는 팀명 및 게임 결과의 양식은 다음과 같다. 팀명에는 띄어쓰기가 없으며, 팀명과 스코어(스코어 < 10)간에는 띄어 쓰기로 구분되어 있다.<br>
<br>
<br>
한 조에 있는 팀의 수<br>
팀1<br>
팀2<br>
...<br>
팀명A 스코어[a:b] 팀명B<br>
...<br>
<br>
출력해야 하는 순위표의 양식은 다음과 같다.<br>
순위) 팀명 승 패 세트[이긴세트-진세트] 세트득실점<br>
...<br>
순위표에서 각 카테고리는 띄어 쓰기로 구분하며, 팀명은 20자를 넘지 않는다.<br>

### 실행 화면 예시

<img src="/img/6-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

typedef struct team{
	char name[22]; //팀명
	int plus; //득점
	int minor; //실점
	int win; //이긴수
	int lose; //진수
	int plus_minor; //득실점(득점-실점)
	int winner[10]; //해당 팀과 경기에서 이겼는지의 여부를 1과 0으로 표기
}team;

void cal_score(team *list, char *buf, int count)
{
	int i,score_index=0,k,s;
	int key;
	int lose_index;
	int win_index;
	
	while(!(buf[score_index]==':' && buf[score_index-1] >= '0' && buf[score_index-1] <= '9' && buf[score_index+1] >= '0' && buf[score_index+1] <= '9'))
		score_index++; //팀명을 건너뛴다.
	for(i=0;i<count;i++)
	{
		k = 0;
		key = 0;
		while(list[i].name[k]) //동일한 팀명을 가진 팀명을 찾는다.
		{
			if(list[i].name[k] == buf[k])
			{
				k++;
				continue;
			}
			else
			{
				key = 1; //동일한 팀명이 아니면 key = 1;
				break;
			}
		}
		if (key == 0) //동일한 팀명을 찾았을 경우
		{
			list[i].plus+=(buf[score_index-1] -'0'); //왼쪽에서 해당 팀명을 찾았으므로, 득점은 왼쪽, 실점은 오른쪽이다.
			list[i].minor+=(buf[score_index+1] -'0');
			if(buf[score_index-1] > buf[score_index+1]) //스코어가 더 큰 경우
			{
				list[i].win++; //승리횟수를 늘려준다.
				win_index = i; //해당팀의 인덱스도 따로 저장한다.
			}
			else //진 경우
			{
				list[i].lose++; //진횟수를 늘려주고
				lose_index = i; //해당팀의 인덱스를 저장한다.
			}
			break;
		}
	}
	for(i=0;i<count;i++)
	{
		s = score_index+3; //:로부터 3만큼 더하면 팀명이 나온다.
		k = 0;
		key = 0;
		while(list[i].name[k]) //위에서와 마찬가지로 팀명이 같은 경우를 찾아본다.
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
		if (key == 0) //팀명이 같을 경우
		{
			list[i].plus+=(buf[score_index+1] -'0'); //오른쪽의 스코어가 득점, 왼쪽의 스코어가 실점이다.
			list[i].minor+=(buf[score_index-1] -'0');
			if(buf[score_index+1] > buf[score_index-1]) //이긴팀, 진팀을 구분해서 인덱스와 횟수를 늘려준다.
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
	list[win_index].winner[lose_index] = 1; //이긴팀의 winner에서 진팀의 인덱스를 1로 설정한다.
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort(team *list, int *index, int count) //1. 승리 수, 2. 승리 수가 같은 경우, 세트 득실점, 3. 그것도 같다면 해당 팀과의 승부에서 이긴 팀을 우선 순위로 둔다.
{
	int i,j,max;
	for(i=0;i<count;i++)
	{
		max = i;
		for(j=i+1;j<count;j++)
		{
			if((list[index[j]].win > list[index[max]].win) || //승리횟수 비교
			((list[index[j]].win == list[index[max]].win) && (list[index[j]].plus_minor > list[index[max]].plus_minor)) || //승리횟수가 같고, 세트 득실점을 비교
			((list[index[j]].win == list[index[max]].win) && (list[index[j]].plus_minor == list[index[max]].plus_minor) && (list[index[j]].winner[index[max]] == 1)))
				max = j;//마지막으로 이긴 횟수와, 세트 득심점이 같은 경우에는 winner 인덱스가 1인 팀을 우선 순위로 둔다.
		}
		swap(&index[i], &index[max]);
	}
}

void init_list(team *list, int count)
{
	int i,j;
	for(i=0;i<count;i++) //널값이 들어가는 것을 방지하기 위해 0으로 초기화 시켜준다.
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
		for(i=0;i<count;i++) //count는 팀의 수
		{
			fgets(list[i].name,22,stdin); //팀명을 읽어 들인다.
			k = 0;
			while(list[i].name[k] != '\n')
				k++;
			list[i].name[k] = '\0'; // '\n' 대신에 '\0'으로 바꾼다. fgets의 개행문자를 없애기 위해.
		}
		init_list(list,count); //0으로 초기화
		match = (count)*(count-1)/2; //경기의 횟수 = 팀의 수 * 팀의 수 -1 / 2
		for(i=0;i<match;i++) //경기 수만큼 읽어와서 스코어를 업데이트 시켜준다.
		{
			fgets(buf,1024,stdin);
			cal_score(list, buf, count);
		}
		for(i=0;i<count;i++) //인덱스를 팀 개수 만큼 초기화 & 각 세트득실점 계산
		{
			index[i] = i;
			list[i].plus_minor = list[i].plus - list[i].minor;
		}
		sort(list,index,count); //문제에서 요구하는 순서대로 팀 정렬
		for(i=0;i<count;i++) //문제에서 요구하는 요소들을 출력해준다.
		{
			k = index[i];
			printf("%d) %s %d %d %d-%d %d\n",i+1, list[k].name, list[k].win, list[k].lose, list[k].plus, list[k].minor, list[k].plus_minor);
		}
	}
}
```
