# 10주차-백트래킹2

## 문제 1

### 문제설명

<교재 61번 문제와 동일, 단, 교재에 있는 소스코드는 오류가 있으므로 그대로 사용하면 문제 발생><br>
<br>
줄다리기는 두 편에 있는 사람들이 서로 반대 방향으로 밧줄을 잡아당기는, 힘을 겨루는 시합이다. <br>
자기편 쪽으로 밧줄을 끌어오는 데 성공한 편이 경기에 이기게 된다.<br>
사무실 야유회에서 줄다리기를 하기로 했다. 야유회에 참가한 사람들을 두 편으로 공평하게 나눈다.<br>
모든 사람들이 둘 중 한 편에 참여해야 하며, 두 편의 사람 수는 한 명이 넘게 차이가 나면 안 된다.<br>
그리고 양 편에 속한 사람들 체중의 총합 차를 최소한으로 줄여야 한다.<br>
<br>
첫번째 줄에는 테스트 케이스의 수가 입력되고, 그 다음 줄은 빈줄이 입력된다.<br>
각 케이스의 첫번째 줄에는 야유회에 참가한 사람의 수인 n이 입력된다.<br>
그 밑으로 n줄에 걸쳐서 사람들의 체중이 입력된다. (체중은 1 ≤ 체중 ≤ 450인 정수)<br>
총 사람수는 최대 100명이고, 서로 다른 테스트 케이스 사이에는 빈 줄이 하나씩 입력된다.<br>
<br>
각 테스트 케이스마다 한 줄씩의 결과를 출력하며, 각 줄마다 두 개씩의 정수가 출력되어야 한다.<br>
<br>
첫번째 수는 왼편에 속한 사람들의 체중의 총합<br>
다른 수는 다른 편에 속한 사람들의 체중의 총합<br>
이 두 값이 서로 다르면 작은 값을 먼저 출력<br>
두 개의 서로 다른 케이스에 대한 결과는 빈 줄로 구분한다. <br>

### 실행 화면 예시

<img src="/img/10-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#define	abs(x) (((x)<0)?-(x):(x))
//10-1-1.input 3번 테스트케이스에 대해 잘못된 값을 출력하고, 해결하지 못하였다..
int arrsum(int *a, int alen) //해당 그룹의 원소(무게)의 합을 출력해주는 함수
{
    int i;
    int result=0;
    for(i=0;i<alen;i++) result = result+a[i];
    return result;
}

void swap(int *a, int *b) //원소의 자리를 바꿔주는 함수
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void tug(int *a, int *b, int alen, int blen)
{
    if (arrsum(a,alen)==arrsum(b,blen)) //몸무게 총합이 같을 경우 출력
    {
        printf("%d\n", arrsum(a,alen));
        printf("%d\n", arrsum(b,blen));
        return;
    }
    int tdiff;
    tdiff = arrsum(a,alen)-arrsum(b,blen);
    int i,j;
    for(i=0;i<alen;i++)
    {
        for(j=0;j<blen;j++)
        {
            if(abs(2*(b[j]-a[i])+tdiff)<abs(tdiff)) //해당 조건에 해당되는 a원소, b원소가 없다면 아래 if문에 의해 정답 출력.
            {
                swap(&a[i],&b[j]);
                tug(a,b,alen,blen);
                return;
            }
        }
    }
    if (arrsum(a,alen) > arrsum(b,blen)) //몸무게 총합이 다를 경우 작은 것부터 출력
        printf("%d %d\n",arrsum(b,blen), arrsum(a,alen));
    else
    {
        printf("%d %d\n",arrsum(a,alen), arrsum(b,blen));
    }
    return;
}

int main()
{
    int n,i,tcase;
    int a[50], b[50];
    scanf("%d",&tcase);
    getchar();
    while(tcase>0)
    {
        scanf("%d", &n);
        getchar();
        if (n%2==0) //짝수일 경우 반씩 나눠가진다.
        {
            for(i=0;i<n/2;i++) scanf("%d", &a[i]);
            for(i=0;i<n/2;i++) scanf("%d", &b[i]);
            tug(a,b,n/2,n/2);
        }
        else //홀수일 경우 a의 원소가 b원소보다 1개 더 많다.
        {
            for(i=0;i<(n+1)/2;i++) scanf("%d", &a[i]);
            for(i=0;i<(n-1)/2;i++) scanf("%d", &b[i]);
            tug(a,b,(n+1)/2,(n-1)/2);
        }
        tcase--;
        if(tcase>0)
            printf("\n");
    }
    return 0;
}

```

## 문제 2

### 문제설명

박스의 몸체 부분을 b(ox), 덮개 부분을 c(over)이라고 하자.<br>
상자에서 물건이 흘러가나가는 일이 없도록 포장하려면 몸체를 두고 덮개로 덮어야 한다. 이 경우를 "합당한 상태"라고 정의한다.<br>
상자 안에 상자가 들어가는 경우 역시 합당한 상태라고 할 수 있다.<br>
입력으로 0 이상 12 이하의 정수인 n이 주어지면 n개의 상자로 만들 수 있는 모든 합당한 상태를 출력하라.<br>
합당한 상태를 출력하는 순서는 사전순이다. bcbcbc를 bbbccc로 바꿔서 출력하라는 의미가 아니라<br>
bbbccc가 bbcbcc보다 먼저 출력하라는 의미이다.<br>
아래의 입출력 예시를 참고하자.<br>
### 실행 화면 예시

<img src="/img/10-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
//카탈란 수 알고리즘을 이용하여 해결 b가 ( 이고 c가 )로 생각하면 문제이해에 도움이 된다.
void solution(char *buf,int n, int b, int c);

int main()
{
	int n;
	int i;
	char buf[25];
	while(scanf("%d",&n)!=EOF)
	{
		solution(buf,0,n,0);
	}
}

void solution(char *buf,int n, int b, int c)
{
	if (b == 0 && c == 0) //출력조건
	{
		buf[n]=0;
		printf("%s\n",buf);
		return;
	}
	if (b > 0) //b if문이 더 먼저 있어서 box를 우선시 출력.
	{
		buf[n] = 'b';
		solution(buf, n+1, b-1, c+1);
	}
	if (c > 0) //dfs 방식으로 위에서 출력조건이 만족되어 출력된 후 바로 직전부터 c로 채우면서 접근.
	{
		buf[n] = 'c';
		solution(buf,n+1,b,c-1);
	}
}
```

## 문제 3

### 문제설명

어떤 채굴회사가 광산에서 다이아몬드 채굴작업을 시작하려고 한다.<br>
이 회사는 이동비용을 절감하기위해 채굴을 시작하기에 앞서 다이아몬드가 매장되어있는 곳의 구역을 번호매기기로했다.<br>
NxN 크기로 주어진 지도에서 1로 표시된 부분이 다이아몬드가 매장되어 있는 곳의 좌표이다.<br>
다이아몬드가 서로 인접해 있는 곳을 한 구역으로 정의한다. <br>
여기서 인접이라는 것은 상하 또는 좌우로 다이아몬드가 연결되어 있는 것을 이야기한다.대각선상에 있는 경우는 인접한 것이 아니다.<br>
<br>
좌측 최상단부터 탐색을 수행하며, 탐색은 첫째 줄부터 탐색한 후 첫째 줄에서의 구역 탐색이 끝나면 둘째 줄의 탐색을 수행한다.<br>
탐색 중에 먼저 발견한 채굴지역부터 구역 번호를 매겨서 지도에 표시를 한다.<br>
아래 광산지도에서는 구역이 2개로 표시되는데 구역 번호는 1번과 2번이 된다.<br>
단, 지도의 크기는 10*10까지이다.<br>
### 실행 화면 예시

<img src="/img/10-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int n; //맵의 크기(nxn)
int map[10][10]; //맵
int key; //영역을 경계짓는 변수

const int EXIST = -1; //채울 수 있는 공간, 다이야가 있는 공간
const int NONE = 0; // 채우지 못하는 공간, 다이야가 없는 공간

void print_map()
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
}

int exist(void)
{
	int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(map[i][j] == EXIST) //채울 공간이 하나라도 있으면 return 1
				return 1;
	}
	return 0; //채울 공간이 하나도 없으면 return 0
}

int find(int i, int j, int value) //영역을 나눠서 값을 채워주는 함수
{
	if(i<0 || j<0 || i>=n || j>=n) { //인덱스를 넘는 예외처리, value를 다 채울 경우 맵을 순회하다가 인덱스를 넘겨 find가 종료된다.
    	return 0;
    }
	else if(exist() == 0){ //더이상 채울 곳이 없으면 출력
		print_map();
        return 1; //모든 공간을 다 채우면 return 1을 하여 더이상의 재귀호출을 막는다.
    }
	else if (map[i][j] < value && map[i][j] >= 0 && key != 1) //value보다 작으면서, exist가 아니라면
	{
		key = 0;
		while(i<n)
		{
			while(j<n)
			{
				if(map[i][j] < value && map[i][j] >= 0) //exist가 나올 때까지 index 증가.
					j++;
				if(map[i][j] == EXIST) //exist를 찾으면 해당 영역을 value로 채우면 된다.
				{
					key = 1;
					break;
				}
			}
			if (key == 1)
				break;
			i++;
			j=0;
		}
	} //위에서 i,j값을 찾아주고 그 주변에서 값을 채워주는 형태, key값이 1이기 때문에 위의 else if문은 더이상 수행되지 않는다.
	if(map[i][j] == EXIST){ //채울 수 있는 공간이면
		key = 1;
		map[i][j] = value; //값을 채우고, find 재귀를 수행한다.(방향 순서는 상관없음)
        if(find(i, j+1,value) || find(i+1, j,value)
		|| find(i, j-1, value) || find(i-1,j,value)) {
			return 1;
    	}
    }
	return 0;
}

int main()
{
	int i,j,k;
	char buf[1024];
	while(scanf("%d",&n)!=EOF)
	{
		getchar();
		for(i=0;i<n;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<n;j++)
			{
				map[i][j] = buf[k]-'0';
				if (map[i][j] == 1)
					map[i][j] = -1; //1일 경우 exist로 설정
				k+=2;
			}
		}
		i = 1;
		while (exist()!=0) //더이상 채울 공간이 없을 때까지 value를 증가시키며 영역을 채움.
		{
   			key = 0;
			find(0,0,i);
			i++;
		}
	}
}

```
