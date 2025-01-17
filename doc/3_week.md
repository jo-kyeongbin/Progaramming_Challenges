# 3주차-자료구조2

## 문제 1

### 문제설명

 __<참고: 문제 11 – 동맹 휴업>__ <br>
어떤 나라의 정당들은 정기적인 동맹 휴업(파업)을 추진하는데, 이 동맹 휴업이 국민들을 힘들게 하고, 경제에 상당한 피해를 끼치다 보니 결국에는 동맹 휴업 추진에 앞서 두 가지 규칙을 도입하기로 했다.<br>
1. 매 주 수요일은 ‘무조건 일 하는 날’로 정하여 동맹 휴업을 할 수 없다.
2. 정당들 중 반 이상이 동맹 휴업을 추진한 날에만 휴업을 할 수 있도록 한다.

이 문제에서는 각 당을 동맹 휴업 지수라고 부르는 h라는 양의 정수로 나타낼 수 있다고 하자. <br>
동맹 휴업 지수는 한 동맹 휴업과 다음 동맹 휴업 사이의 기간을 날짜 수로 표시한 값이다.<br>
3개의 정당이 있다고 하자. i번째 당의 동맹 휴업 지수를 h(i)라고 할 때, h(1) = 3, h(2) = 4, h(3) = 8이라고 가정하겠다. <br>
n(n = 14)일 동안의 3당의 행보를 시뮬레이션 하면 다음과 같이 표시할 수 있다.<br>
시뮬레이션은 항상 일요일에 시작하며 주말은 휴일이므로 동맹 휴업이 없다고 가정한다.<br>

<img src="/img/3-1-1.jpeg" width="60%" height="60%">

이 결과를 보면 14일 동안 1번의 동맹 휴업(12일)이 있음을 알 수 있다. <br>
3, 6, 9일의 경우 휴업을 해도 되는 날이긴 하지만 반 이상의 정당이 추진하지 않았으므로 휴업이 일어나지 않았고, 8일은 반 이상의 정당이 휴업을 추진하였으나 주말이기에 동맹 휴업이 일어나지 않았다. <br>
4일은 반 이상의 정당이 추진하지도 않았지만, 만약에 추진한 정당이 둘 이상이었다고 하더라고 수요일이므로 휴업이 추진되지 않는다.<br>
입력으로 테스트케이스의 수가 먼저 주어지고, 그 다음 줄부터는 시뮬레이션을 위한 일수 n과 몇 정당의 동맹 휴업 지수가 주어졌을 때, <br>
n일 가운데 동맹 휴업으로 인해 일을 하지 않은 근무 일수를 계산하고, 휴업을 하는 요일과 날짜를 출력하라.<br>
입력을 간략하게 정리하여 보자면,<br>

* c (테스트 케이스의 수)
* n (시뮬레이션을 할 날짜 수)
* p (정당의 수)
* h(1) (1번 정당의 휴업 지수)
* ..
* h(p) (p번 정당의 휴업 지수)

이렇게 된다.<br>
출력은 다음과 같다.<br>

* Lost: 동맹 휴업으로 인해 일을 하지 못한 근무 일수
* (휴업 하는 날의)요일 이름: 날짜
* ...

출력 문에서 각 테스트 케이스들 사이에는 빈 줄 하나를 삽입하도록 하며, <br>
요일 이름의 경우 일요일부터 토요일까지 Sun, Mon, Tue, Wed, Thu, Fri, Sat의 양식으로 표현하면 된다. <br>
Lost: 와 숫자 사이, 요일: 과 숫자 사이에는 반드시 공백이 하나 있어야 한다.<br>
자세한 것은 아래에 설명된 입출력 예시를 확인하자.<br>

### 실행 화면 예시

<img src="/img/3-1-2.png" width="60%" height="60%">
<img src="/img/3-1-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

void print_day(int day) //요일과 날짜를 출력해주는 함수
{
    int result = day % 7;

    switch (result)
    {
        case 1:
            printf("Sun: %d\n",day);
            break;
        case 2:
            printf("Mon: %d\n",day);
            break;
        case 3:
            printf("Tue: %d\n",day);
            break;
        case 4:
            printf("Wed: %d\n",day);
            break;
        case 5:
            printf("Thu: %d\n",day);
            break;
        case 6:
            printf("Fri: %d\n",day);
            break;
        case 0:
            printf("Sat: %d\n",day);
            break;
    }
}


int main() {
    int tCase, day, poli, i, j, lost, k, p, r; //tCase = 테스트케이스 저장 변수, day = 전체 날짜 수, poli = 정당의 수, lost = 총 휴업일
    int buf[1024];
    lost = 0;
    p = 0;
    scanf("%d",&tCase);



    while(tCase--){
        scanf("%d",&day);
        scanf("%d",&poli);


        int hartal[poli];
        
        for(i=0; i<poli; i++){
            scanf("%d",&hartal[i]);
        }

        for(j=1; j<day+1; j++){ //날짜는 1부터 시작하기 때문에 1~day만큼 루프를 돈다.
            r = 0;
            for(k=0; k<poli; k++){ //정당의 수 만큼 루프를 돈다.
                if(j%hartal[k]==0){ //해당 정당의 휴업일일때,
                    if(!((j%7==1 || j%7==0) || (j%7==4))){ //일요일, 토요일, 수요일은 동맹휴업을 하지 않기로 하였음.
                        r++; //해당 정당 카운트
                        if (r >= (poli+1)/2) //해당 정당 수가 과반수로 정해지면
                        {
                            lost++; //쉬는날로 카운트
                            buf[p++]=j; //요일과 날짜를 출력해주기 위해 해당 날짜를 버퍼에 저장
                            r = 0;
                            break; //이미 정당의 수가 과반수를 넘겨 동맹휴업일로 지정되어 다음 정당을 고려하지 않기 위해 루프를 종료 시킨다.
                        }
                    }
                }
            }
        }

        printf("Lost: %d\n",lost); //총 동맹 휴업일 출력해준다.
        for (i=0;i<p;i++)
            print_day(buf[i]); //버퍼에 저장된 동맹휴업일의 요일과 날짜를 출력해준다.
		if (tCase!=0)
            printf("\n");
        lost = 0; //테스트케이스만큼 수행하기 위해 변수를 초기화시켜준다.
        p = 0;
    }
   return 0;
}
```

## 문제 2

### 문제설명

레스토랑에서 주문은 무조건 온 순서대로 받고, 식사를 마치는 것도 같은 순서대로라고 가정하자.<br>
단, 이 레스토랑에는 자리가 몇 개밖에 없는데다, 자리가 꽉 차 있을 때 온 손님은 기다리지 않고 돌아가 버린다.<br>

첫째 줄에는 레스토랑에 자리가 몇 개 있는지가 입력된다 (자리는 최대 26개).<br>
둘째 줄에는 손님이 오는 것은 알파벳으로(A에서 Z까지), 식사를 마치는 것은 *로 표시되어 있다.<br>
가장 마지막 손님이 들어온 뒤 아직 자리에 남아 식사를 하고 있는 손님들은 누구인지, 또한 빈자리는 어디인지 순서대로 출력하자. 이때 빈 자리는 #으로 표기한다.<br>
자리에 앉을 때 무조건 앞쪽(맨 왼쪽)의 빈 자리부터 채워 앉는다.<br>

예제에서는 A B C가 와서 자리에 앉고, D가 왔을 때 자리가 꽉 차 돌아갔으며, *가 한 번 있었을 때 A가 식사를 마쳤고, 그 다음 E가 왔고, *가 두 번 있었으니 B와 C가 식사를 마쳤으며, 그 다음 F가 왔고, *에서는 E가 식사를 마치고 마지막으로 G가 왔다. 따라서 아직 식사를 하고 있는 사람과 빈 의자는 순서대로 G F #가 된다.<br>

입력: 자리상태<br>
A: A # #<br>
B: A B #<br>
C: A B C<br>
D: A B C<br>
*: # B C<br>
E: E B C<br>
*: E # C<br>
*: E # #<br>
F: E F #<br>
*: # F #<br>
G: G F #<br>

### 실행 화면 예시

<img src="/img/3-2.png" width="60%" height="60%">

### 코드
```c
/*FIFO 형태의 자료형을 가진다. 먼저 들어온사람이 먼저 식사를 마친다.*/
#include <stdio.h>

int main(){
	int tables, i, k, min_index, key; //tables=테이블수, min_index=제일 먼저들어온 손님 저장, key=min_index의 초기값을 제어해주기 위한 변수.
	char buf[1024];

	scanf("%d",&tables);
	getchar(); //개행 문자를 없애주기 위한 표현
	char exist[tables];
	for(i=0;i<tables;i++) //비어있는 테이블로 초기화
		exist[i] = '#';
	scanf("%[^\n]s",buf); //개행문자를 무시하기 위한 표현
	i = 0;
	min_index = 0;
	while (buf[i])
	{
		if ('A'<=buf[i] && 'Z'>=buf[i])
		{
			for (k = 0;k < tables;k++)
			{
				if (exist[k] == '#') //비어있는 테이블이면 자리를 해당 문자로 채운다.
				{
					exist[k] = buf[i];
					break; //비어있는 테이블을 발견하여 자리를 찾았으므로, 반복문 종료.
				}
			}
			i++;
			continue;
		}
		if (buf[i] == '*') //식사를 마쳤다면
		{
			key = 0;
			for (k=0; k<tables; k++)
			{
				if (exist[k] != '#' && key == 0) //min_index의 초기값을 지정해주기 위해 key를 이용했다.
				{	
					min_index = k;
					key = 1;
				}
				if (exist[k] != '#' && exist[min_index] > exist[k]) //먼저 들어온 손님의 문자가 더 작으므로 (ex)A가 B보다 일찍 들어왔다.)
				{
					min_index = k;
				}
			}
			exist[min_index] = '#'; //일찍 들어온 손님이 식사를 마쳐서 비워줬다.
			i++;
			continue;
		}
		i++; //공백을 건너뛰기 위한 i++
	}
	for (k=0;k<tables;k++) //결과값 출력
	{
		if (k != tables - 1)
			printf("%c ",exist[k]);
		else
			printf("%c\n",exist[k]);
			
	}
}
```

## 문제 3

### 문제설명
빨강 마을 티모는 협곡에서 버섯 농장 아르바이트를 한다. 농장에선 매 시간마다 티모에게 하나의 명령을 내린다.<br>
티모가 수행하는 명령의 종류에는 R(뒤집기), B(가장 큰 버섯 버리기), S(가장 작은 버섯 버리기)가 있다. 다른 명령은 못본척한다.<br>
R은 버섯 리스트의 순서를 뒤집는 명령, B는 버섯 리스트 중 크기가 가장 큰 버섯을 버리는 명령, S는 가장 작은 버섯을 버리는 명령이다. (단, 가장 큰 또는 가장 작은 버섯이 여러 개 있다면 가장 왼쪽에 있는 버섯을 버린다.)<br>

리스트에 버섯이 존재하지 않을 경우에 명령이 내려진 경우 오류가 발생한다.<br>
게으른 티모는 이 명령들을 한번에 모아서 처리하고 싶어한다.<br>
예를 들어, "RBS"라는 명령은 R을 수행하고 B를 수행한 다음, 마지막으로 S를 수행하는 명령어다.<br>
버섯 리스트의 초기값과 수행할 명령이 주어졌을 때, 최종 버섯 리스트를 출력하라.<br>
만약, 오류가 난 경우에는 "No mushrooms!"를 출력하고, 리스트가 빈 경우에는 "Empty!"를 출력한다.<br>
명령어가 올바르지 못한 경우 "Wrong Command!"를 출력한다.<br>

------

입력<br>
첫째 줄에 배열의 크기(버섯의 개수) N이 주어진다.(0 <= N <= 1,000)<br>
둘째 줄에 배열에 넣을 수(버섯의 크기) Xi가 주어진다.(1 <= Xi <= 1,000,000)<br>
셋째 줄에 수행할 명령어 p가 주어진다.(1 <= p <= 100,000)<br>
<br>
출력<br>
각 테스트케이스에 대해서 입력으로 주어진 배열에 대한 최종 결과를 출력한다.<br>

### 실행 화면 예시

<img src="/img/3-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#include <stdlib.h>
/*어떤 상황에 No mushroom, empty, Wrong command인지 구별하는 것이 중요하다.*/
void reverse(int *size, int count) //버섯의 순서를 뒤집는 함수
{
	int i;
	int temp[count];
	for(i=0;i<count;i++)
		temp[i] = size[count -1 -i]; //버섯의 개수가 count이므로 count-1이 인덱스로 된다.
	for(i=0;i<count;i++)
		size[i] = temp[i];
}

int get_length(char *s) //문자열의 길이를 측정하는 함수
{
	int i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return i;
}

int my_atoi(char *buf) //문자열을 정수형으로 바꿔주는 함수
{
	int i;
	int length = get_length(buf);
	int result;
	result = buf[0] - '0'; // 초기값 설정, '0'(45)을 빼면 숫자값이 나온다.
	for(i=1;i<length - 1;i++) //i = 0부터 시작하려면 처음에 result = 0을 넣고 for문을 i = 0부터 시작하면 된다.
		result = (result * 10) + (buf[i] - '0');
	return result;
}

int main()
{
	char *buf; //버섯의 리스트를 받는 버퍼
	int temp;
	char *op;
	int *result;
	int size[1000];
	char count_buf[6];
	int count, i, k, index, key;
	while(fgets(count_buf,6,stdin)!=NULL){
	count = my_atoi(count_buf); //읽어온 문자열을 정수로 변환, count_buf는 버섯의 개수를 의미한다.
	if (!(count >= 0 && count <= 1000)) //버섯의 개수 제한 (0부터 1000까지만 가능)
	{
		printf("Wrong Command!\n");
		continue;
	}
	buf = (char *)malloc(sizeof(char)*2048);
	scanf("%[^\n]s",buf); //개행을 무시하여 버섯의 리스트를 받는다.
	i=0;
	temp = 0; //문자열로 들어온 버섯의 크기를 int로 변경해준 결과를 저장해주는 변수.
	k = 0;
	key = 0;
	while (buf[i] && key == 0) //잘못된 명령어를 입력하였을 때, key가 1이 되어 반복문 종료.
	{
		while (buf[i] != ' ' && buf[i]) //my_atoi를 사용하지 않은 이유는 공백을 기준으로 문자열만 숫자로 변경하면 되기 때문입니다.
		{//while문에 buf[i]가 있는 이유는 널문자를 넘기면 세그멘테이션 오류가 발생합니다.
			if (buf[i] >= '0' && buf[i] <= '9')
				temp = (temp * 10) + (buf[i] - '0');
			i++;
		}
		if (k < count) //버섯의 개수를 넘기지 않으면 버섯의 크기를 size에 저장해준다.
		{
			if (temp >= 1 && temp <= 1000000)
				size[k++] = temp;
			else //버섯의 크기의 범주를 넘는 버섯이 들어오면 Wrong Command!
			{
				printf("Wrong Command!\n");
				key = 1;
			}
		}
		temp = 0;
		if (buf[i]) //라인60의 while문이 종료되거나, 애초에 공백문자일 경우, 즉 공백문자를 건너뛰기 위해 i++수행
			i++;
	}
	op = (char *)malloc(sizeof(char)*100000);
	scanf("%s",op); //명령어 리스트를 받는다.
	getchar();
	i = 0;
	while (op[i] && key == 0) //key는 No mushrooms를 발생하였을 때 1이 된다.
	{
		switch(op[i])
		{
			case 'R':
				index = 0;
				while (index < count) //버섯의 개수만큼 반복문 수행
				{
					if(size[index] > 0) //버섯이 존재하면, 즉 0보다 큰 버섯이 존재하면 종료
						break;
					index++;
				}
				if (index == count && size[index] == 0) //버섯이 존재하여 중간에 종료됐으면, index가 count랑 다르고, size[index]가 0이 아니다.
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				reverse(size,count); //버섯이 존재하기 때문에 R명령수행.
				break;
			case 'S':
				index = 0;
				while (index < count) //마찬가지로 버섯이 존재하는지 여부를 파악.
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
						if(size[k]<size[index] && size[k] != 0) //버섯을 비교하여 0이 아닌 작은 값에 대해 최소값이 나오면 해당 인덱스를 저장한다.
							index = k;
					}
				}
				if (size[index] != 0)
					size[index] = 0; //S명령을 수행하여 제일 작은 버섯을 지운다.
				break;
			case 'B':
				index = 0;
				while (index < count) //마찬가지로 버섯의 존재여부를 파악한다.
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
						if(size[k]>size[index] && size[k] != 0) //이번에는 제일 큰 버섯을 찾는다.
							index = k;
					}
				}
				if (size[index] != 0)
					size[index] = 0; //B명령을 수행하여 제일 큰 버섯을 지운다.
				break;
			default:
				printf("Wrong Command!\n"); //R 또는 B 또는 S가 아닌 경우 잘못된 명령어이다.
				key = 1;
		}
		i++;
	}
	k = 0;
	result = (int *)malloc(sizeof(int)*1024);
	for (i=0;i<count;i++) //결과를 출력해주기 위해 result 배열에 0이 아닌 값을 담는다.
	{
		if (size[i] > 0)
			result[k++] = size[i];
	}
	if (k == 0 && key == 0) //size가 0보다 큰 버섯이 없으면서, 즉 버섯이 존재하지 않으며, 위에서 오류를 발생하지 않았다면)
		printf("Empty!\n");
	if (key == 0 && result[0] != '\0') //오류 발생한 적없고, 결과값이 비어있지 않으면 결과값 출력.
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
```
