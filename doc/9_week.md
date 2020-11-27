# 9주차-백트래킹1

## 문제 1

### 문제설명

체스판에서 Queen(여왕)이 서로가 서로의 이동경로가 아닌 위치에 있도록 최대한 많은 퀸을 체스판 위에 놓는 문제이다.<br>
조건은 다음과 같다.<br>
<br>
어떤 두 개의 퀸도 다른 퀸과 같은 열이나 같은 행 위에 있으면 안되고, 대각선으로 연결할 수 있는 위치에 있어서도 안 된다.<br>
입력은 사용자로부터 10보다 작은 숫자 하나 N을 입력 받는다. 입력받은 숫자 N은 N*N의 체스판의 크기와 N개의 Queen개수를 나타낸다.<br>
N개의 Queen문제는 대칭성이 존재한다. 해결할 때 테이블이 좌측 상단부터 행을 기준으로 열을 증가시키면서 Queen이 놓이는 위치를 판단한다.<br>
한 행의 모든 열의 탐색이 끝나면 다음 행으로 넘어가는 방식을 취한다. Queen의 위치를 출력할 때도 마찬가지로 수행한다.<br>
<br>
### 실행 화면 예시

<img src="/img/9-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#define ABS(x)  (((x)<0)?-(x):(x)) //절대값 매크로 함수

int N;
int board[10]; //각 행에서의 어느 열에 존재하는 지 여부를 저장해주는 변수. (값: 열 위치)

int possible(int row) { //해당 자리에 퀸이 올 수 있는지 여부를 판단해주는 함수
    for (int i = 0; i < row; i++) {
        if (board[i] == board[row] || (row - i) == ABS(board[i] - board[row])) { //같은 열에 있거나 대각선에 존재하면 return 0
            return 0;
        }
    } 
    return 1; //조건을 만족하면 return 1
}

void setQueen(int row) { 
    int i;
    int j;
    if (row == N) { //모든 퀸의 위치를 정하였을 때 출력해준다.
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                if(j==board[i])
                    printf("Q ");
                else
                    printf("* ");
            }
            printf("\n");
        }
        printf("\n");
    }
    else { //dfs이다. 우선 조건에 맞는부분을 출력해주고,
        for (int col = 0; col < N; col++) {//바로 직전 단계부터 살펴보아 for문이 다시 수행되어 조건을 만족하는 부분을 찾는다.
            board[row] = col; //우선 퀸의 위치를 정한다.

            if (possible(row)) {  //조건에 맞는 지 확인하고, 충족한다면
                setQueen(row + 1); //다음 행을 고려한다.
            }
        }
    }
}

int main(void) {
    while (scanf("%d", &N)!=EOF)
    {
        setQueen(0);
    }
    return 0;
}
```

## 문제 2

### 문제설명

0과 1로 이루어진 수열이 있다.<br>
각 수열은 한 단계가 지날 때마다 왼쪽 이웃 숫자와 오른쪽 이웃 숫자의 상태에 따라 값이 변한다.<br>
이웃 숫자가 같으면 현재 값을 유지하고 같지 않으면 값이 변한다.<br>
<br>
수열은 처음과 끝이 이어져 있다고 가정한다. 즉, N개의 수열에서 첫번째 숫자의 오른쪽 이웃은 두번째 숫자이고, 왼쪽 이웃은 N번째 숫자이다.<br>
<br>
예시는 다음과 같다.<br>
<br>
초기값 : 01101<br>
다음값 : 00001<br>
<br>
한 수열이 주어 졌을 때 이전의 상태를 구하여 출력하여라.<br>
이전 상태가 여러 개인 경우 "multiple"<br>
이전 상태가 없을 경우 "zero"를 출력한다.<br>
입력 수열의 길이는 3에서 10사이이다.<br>
<br>
### 실행 화면 예시

<img src="/img/9-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

char answer[11];
char correct[11];
char temp[11];
char buf[1024];
int count;
int N;

int my_strcmp(char *s1, char *s2) //두 문자열을 비교해주는 함수, 완전히 같으면 return 1 하나라도 다르면 return 0
{
	int i=0,j=0;
	while(s1[i] && s2[j])
	{
		if (s1[i] == s2[j])
		{	
			i++;
			j++;
		}
		else
			return 0;
	}
	return 1;
}

void my_strcpy(char *s1, char *s2) //문자열 s1에 문자열 s2의 내용을 복사하고 널을 붙인다.
{
	int i=0;
	while(s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

void find(int pos)
{
	int i;
	if (pos==N) //재귀함수 호출이 종료되는 부분, pos가 입력값의 길이가 되었을 경우.
	{
		for(i=0;i<N;i++) //answer를 문제에서 요구하는 순열대로 구현하여 temp에 저장한다. 즉 answer는 이전 상태.
		{
			if (i==0) //처음부분(처음부분과 끝부분은 연결되어 있으므로 따로 분리하여 처리)
			{
				if (answer[N-1] == answer[1])
					temp[i] = answer[i];
				else
				{
					if (answer[i] == '0')
						temp[i] = '1';
					else
						temp[i] = '0';
				}
			}
			else if(i==N-1) //끝부분
			{
				if (answer[N-2] == answer[0])
					temp[i] = answer[i];
				else
				{
					if (answer[i] == '0')
						temp[i] = '1';
					else
						temp[i] = '0';
				}
			}
			else // 그 외 중간부분
			{
				if (answer[i-1] == answer[i+1])
					temp[i] = answer[i];
				else
				{
					if (answer[i] == '0')
						temp[i] = '1';
					else
						temp[i] = '0';
				}
			}
		}
		answer[N] = '\0';
		temp[N] = '\0';
		if(my_strcmp(temp,buf)==1) //입력값과 temp가 같다면
		{
			count++; //정답 횟수 증가
			my_strcpy(correct,answer); //정답을 따로 저장한다.
		}
	}
	else{ //해당 length를 충족하는 모든 경우의 수를 순회
		answer[pos] = '0'; //해당 부분이 0일 때 재귀호출
		find(pos+1);
		answer[pos] = '1'; //해당 부분이 1일 때 재귀호출
		find(pos+1);
	}
}

int my_strlen(char *buf) //문자열의 길이를 측정하는 함수
{
	int i = 0;
	while(buf[i]!='\n' && buf[i])
		i++;
	return(i);
}

int main()
{
	while(fgets(buf,1024,stdin)!=NULL)
	{
		N = my_strlen(buf);
		buf[N] = '\0';
		count = 0;
		find(0);
		if (count == 1) //이전 상태가 하나일 경우 답을 출력
			printf("%s\n",correct);
		else if(count > 1) //이전 상태가 여러개면 multiple
			printf("multiple\n");
		else //이전 상태가 존재하지 않으면 zero
			printf("zero\n");
	}
}
```

## 문제 3

### 문제설명

미로가 주어진다. 이동할 수 있는 곳은 '1', 이동할 수 없는 곳은 '0', 목적지는 '2'로 표현된다.<br>
출발하는 곳은 좌측 상단인 (0, 0)지점이다.<br>
출발지로부터 목적지까지 갈 수 있는 모든 경로를 구해 출력하고, 각각에 걸리는 이동 수를 출력하라.<br>
단, 목적지에 도달하지 못하는 경우는 없다.<br>
경로를 구하는 데에는 다음과 같은 규칙을 따른다.<br>
<br>
1. 한 번 들렀던 곳을 다시 들를 수는 없다.<br>
2. 이동에 있어서의 우선 순위는 '우측 → 하단 → 좌측 → 상단'이다.<br>
3. 출력에 있어서도 2번의 우선순위를 따라야 한다.<br>
<br>
입력으로는 미로의 행의 크기인 x와 열의 크기인 y가 먼저 들어오고, 그 다음 줄부터 미로의 모양이 들어온다.<br>
<br>
단, x < 10, y < 10이고, 가능한 경로의 개수는 100개 미만이다.<br>
<br>
각 경로를 출력한 후에는 이동 수를 출력하고 빈 줄을 하나 삽입한다.<br>

### 실행 화면 예시

<img src="/img/9-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int count;
int row, col; //행, 열
int map[10][10]; //맵

const int PATHWAY = 1; //갈 수 있는 곳
const int BLOCKED = 4; //막혀있는 곳
const int PATH = 3; //지나간 곳
const int DST = 2; //목적지

void print_map() //정답(맵)을 출력해주는 함수
{
	int i,j,count;
	count = 0;
	for (i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if (map[i][j]==PATH)
			{
				printf("1 ");
				count++;
			}
			else if(map[i][j] == DST)
			{
				printf("%d ",DST);
				count++;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("%d\n",count); //도착지를 포함한 경로의 수를 출력
}


void find(int i, int j)
{
	if(i<0 || j<0 || i>=row || j>=col) return ; //인덱스를 벗어나는 부분을 예외처리
	else if(map[i][j] != PATHWAY && map[i][j] != 2) return ; //도착지가 아니면서 갈 수 없는 길이면 제외
    else if(map[i][j]==DST) { //목적지에 도달하면 정답 출력
		if (count > 0) //결과가 여러개이면
			printf("\n");
		print_map();
		count++;
    }else {
        map[i][j] = PATH; //해당 길을 지나온 길로 표시
		//문제에서 요구한대로 순회 (우측-하단-좌측-상단)
        find(i, j+1);
		find(i+1, j);
		find(i, j-1);
		find(i-1, j);
	if (map[i][j]==PATH) //dfs로 바로 직전의 결과를 다시 안간 것으로 처리하여 다른 길을 찾아본다.
		map[i][j] = PATHWAY;
    }
}

int main()
{
	int i,j,k;
	char buf[1024];
	while(scanf("%d %d",&row,&col)!=EOF)
	{
		getchar();
		for(i=0;i<row;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<col;j++)
			{
				map[i][j] = buf[k]-'0';
				k+=2; //공백이 존재하여 짝수 인덱스만 맵에 저장.
			}
		}
		count = 0; //출력결과가 여러개이면 공백을 추가하기 위한 변수
   		find(0,0);
	}
}
```
