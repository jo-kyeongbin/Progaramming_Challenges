# 4주차

## 문제 1

### 문제설명

두 영어 단어가 철자의 순서를 뒤바꾸어 같아질 수 있을 때, 이 두 단어는 애너그램(anagram) 관계에 있다고 한다.<br>
예를 들어, occurs와 succor는 서로 애너그램 관계에 있다고 할 수 있는데, occurs의 각 문자들의 순서를 잘 바꾸면 succor이 되기 때문이다.<br>
두 개의 영어 단어가 주어졌을 때, 단어가 서로 애너그램 관계에 있도록 만들기 위해 제거해야하는 최소 개수의 문자 수를 구하여라.<br>
문자를 제거할 때에는 위치에 상관없이 제거할 수 있다.<br>

------

입력<br>
첫째 줄과 둘째 줄에 영어 단어가 소문자로 주어진다. 각 단어의 길이는 1이상, 1000 이하이다.<br>
<br>
출력<br>
제거해야 할 문자의 최소 개수를 출력한다.<br>
이 때, 최소 개수는 두 단어 각각 제거되는 문자 개수의 합이다.<br>

### 실행 화면 예시

<img src="/img/4-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int len(char *s) //문자열의 길이를 측정해주는 함수
{
	int i = 0;
	while(s[i])
		i++;
	if (s[i-1] == '\n') //개행을 받아들이는 fgets일경우 크기는 i-1
		return (i-1);
	else 
	{
		return (i);
	}
	
}

int	iter(char *str, char c) //문자열 str에서 문자 c가 발견되면 '0'으로 바꾸고 리턴 1을 해준다.
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == c)
		{
			str[i - 1] = '0';
			return (1);
		}
	return (0);
}

int	main()
{
	char buf1[1002];
	char buf2[1002];
	int i = 0;
	int count = 0;
	while (fgets(buf1,1002,stdin)!=NULL)
	{
		fgets(buf2,1002,stdin);
		while (buf1[i]!='\n')
		{
			if (iter(buf2, buf1[i])) //만약에 buf2에 문자 buf[i]가 있다면 count 증가
				count++;
			i++;
		}
		printf("%d\n",len(buf1) + len(buf2) - (count*2)); //count는 두 문자열 사이에 공통으로 존재하는 문자의 개수이므로, 문제에서 요구하는 문자에서 지워야할 최소 개수는 다음과 같다.
	}
}
```

## 문제 2

### 문제설명

1차 세계대전에 독일군이 사용하던 ‘ADFGVX’라는 암호가 있다.<br>
이 암호를 간략하게 설명하자면, 6*6의 표를 만든 뒤, 그 배열 안에 26자의 알파벳 소문자와 10개의 숫자(0~9)를 무작위로 집어넣는다.<br>
<br>
그리고 1행과 1열은 ‘A’, 2행과 2열은 ‘D’, 3행과 3열은 ‘F’, 4행과 4열은 ‘G’, 5행과 5열은 ‘V’, 6행과 6열은 ‘X’라는 이름을 붙인다. 상기한 설명을 간략하게 표로 작성해보면 다음과 같다.<br>

<img src="/img/4-2-1.jpeg" width="60%" height="60%">

여기에서 행과 열에서 한 자씩 따오는 식으로 암호를 작성한다. “q”의 경우 “AA”로 암호화 시킬 수 있다.<br>
암호문이 “VVAGAVFG AXDFVG”이라고 주어지면, “zera tul”로 해독할 수 있다. 각 행과 열의 이름은 대소문자를 구분하지 않도록 하여, "vvAgAvFg aXDFvg" 역시 "zera tul"로 해독할 수 있다.<br>
<br>
입력으로 행/열의 이름과 배열 안에 채워 넣을 36자의 숫자와 알파벳이 주어지고, 여러 줄로 된 암호문들이 주어진다. 주어진 암호문을 해독하여 출력하면 된다. 해독할 수 없는 경우 에러 메시지를 출력시킨다.<br>
암호문은 알파벳이 대소문자 가리지 않고 들어가 있으며, 숫자나 특수문자가 들어가 있을 수도 있다. 다른 특수문자가 들어 있다면 해독할 수가 없으므로 에러 메시지(-ERROR-)를 출력해야 겠지만, 암호문 안에 띄어쓰기가 있다면 띄어쓰기는 그대로 출력해야 한다. 암호문은 각 줄마다 100자를 넘기지 않는다.<br>

### 실행 화면 예시

<img src="/img/4-2-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int vaildation(char *text, char *s)
{
	int i;
	int key;
	while (*s != '\n')
	{
		key = 0;
		for(i=0;i<6;i++)
		{
			if (*s == text[i] || *s == ' ') //6개의 문자에 포함되는 문자인지 파악한다.
			{
				key = 1;
				break;
			}
		}
		if (key == 0) //해당하는 문자가 아닐경우 반복문 종료.
			break;
		s++;
	}
	if (*s == '\n') //모든 입력문을 순회하였고, 모두 6개의 문자에 포함되면 return 1
		return (1);
	else
		return (-1);
}

int convert_index(char a, char *text)
{
	int i;
	for (i=0;i<6;i++)
	{
		if (text[i] == a) //해당 문자를 인덱스로 변환하여 mapping 시켜준다.
			return i;
	}
	return 0; //validation을 거쳐왔기 때문에 매핑이 안될 이유는 없지만 안되면 인덱스 0에 해당하는 매핑을 하기 때문에 오류를 일으킨다.
}

void upper(char *s) //소문자를 대문자로 변경시켜준다. 문제에서 대소문자를 구분하지 않으므로 하나의 문자로 통일.
{
	int i = 0;
	while(s[i] != '\n')
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
}

int main()
{
	char text[8]; //행과 열의 카테고리 인덱스 총 6자리.
	char map_buf[38]; //순서대로 들어온 36개의 문자
	char map[6][6]; //6x6의 맵
	char buf[102]; //암호문을 받는 버퍼
	char result[100]; //평문을 받는 버퍼
	int i,j,k,p;

	while (fgets(text,8,stdin)!=NULL)
	{
		upper(text);
		fgets(map_buf, 38, stdin);
		k = 0;
		for(i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				map[i][j] = map_buf[k++]; //맵에 입력받은 36개의 문자를 저장해준다.
			}
		}
		while(fgets(buf,102,stdin)!=NULL)
		{
			upper(buf); //모든 암호문을 대문자로 변경
			if((vaildation(text,buf) == -1)) //없는 문자를 암호문에 포함시키면 에러 출력.
			{
				printf("-ERROR-\n");
				continue;
			}
			i = 0;
			p = 0;
			while(buf[i] != '\n')
			{
				if (buf[i] == ' ') //공백은 공백으로 유지
				{
					result[p++] = ' ';
					i++;
					continue;
				}
				if ((buf[i] >= 'A' && buf[i] <= 'Z')) //암호문자는 행과 열, 2문자씩 읽어온다.
				{
					if((buf[i+1] >= 'A' && buf[i+1] <= 'Z'))
					{
						j = convert_index(buf[i++], text); //인덱스로 변환
						k = convert_index(buf[i++], text);
						result[p++] = map[j][k]; //맵에서 찾아와서 result에 저장한다.
					}
					else //페어형태로 들어와야하는데 한개의 문자만 읽히면 맵핑을 못하므로, 에러 출력.
					{
						printf("-ERROR-\n");
						k = -3;
						break;
					}
				}
			}
			if (k != -3) //에러를 출력하지 않았다면 결과 출력.
			{
				result[p] = '\0'; //문자열을 출력해주기 위해 마지막에 널문자 추가.
				printf("%s\n",result);
			}
		}
	}
}
```

## 문제 3

### 문제설명
__<참고: 문제 18 – 월도르프를 찾아라>__<br>
<br>
문자로 이루어진 배열 속에 숨은 Teemo를 찾아라.<br>
위장이 뛰어난 Teemo는 월도르프와는 다르게 이름의 한글자를 변형시켰을 수도 있다.<br>
Teemo, Taemo, heemo, Teemy, Teemm ... 등이 가능하다.<br>
<br>
m*n 배열속에서 좌우대각선 총 8방향으로 찾을 수 있다.<br>
대소문자는 구분하지 않으며 결과로는 찾은 Teemo를 #으로 처리한 문자열을 출력한다.<br>
Teemo가 여러 개가 나오면 모든 Teemo를 다 찾아야 한다.<br>

------

입력<br>
* 첫 번째 줄에는 케이스의 수 (양의 정수)
* 두 번째 줄은 빈칸 (두 개의 다른 케이스 사이에도 빈칸 줄)
* 각 케이스는 한 쌍의 정수 m(행, 1 ~ 50)과 n(열, 1 ~ 50)
* m x n 개의 글자(대소문자)
<br>
출력<br>

* Teemo가 #####으로 표시된 그리드
* 두 개의 서로 다른 케이스에 대한 출력 결과 사이에는 빈 줄을 하나 출력


### 실행 화면 예시

<img src="/img/4-3-1.png" width="60%" height="60%">
<img src="/img/4-3-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

#define M 50
#define N 50
#define BUFFERSIZE 1024
#define DIRECT 8

typedef struct result{
	int direct_index; //방향성을 저장해주는 변수. ex)0이면, (-1,-1) 오른쪽 아래로 향하는 방향
	int start_row; //teemo가 시작되는 행의 인덱스
	int start_col; //teemo가 시작되는 열의 인덱스
}result;

int main() {
    char waldorf[M][N];
	char temp[M][N];
    int testCase, row, col, i, j, k, len, startRow, startCol, direct, t, key=0; //key는 변형된 월도로프를 풀기위한 변수(teemo에서 적어도 한 문자는 달라도 된다.)
	char word[6] = "teemo"; //찾고자 하는 단어

    int dirRow[DIRECT] = {-1,-1,-1,0,1,1,1,0}; //방향성을 알려주기 위한 배열, ex) -1,-1은 행과 열이 하나씩 감소, 즉 오른쪽 아래로 향하는 방향이다.
    int dirCol[DIRECT] = {-1,0,1,1,1,0,-1,-1};
	result answer[300]; //찾은 단어의 위치와 방향성을 저장해주는 구조체 배열.

    scanf("%d",&testCase);
	getchar();
    while(testCase--){
		getchar();
        scanf("%d %d",&row, &col);
		getchar();
        for(i=0; i<row; i++){
            for(j=0; j<col; j++){
                waldorf[i][j] = getchar(); // 한 글자씩 읽어와서 waldorf와 temp에 저장한다.
				temp[i][j] = waldorf[i][j]; //원래의 문자를 저장.
                if(waldorf[i][j] >= 'A' && waldorf[i][j] <= 'Z'){
                    waldorf[i][j] += ('a' - 'A'); //모두 소문자로 변경.
                }
            }
			getchar();
        }
		k = 0;
        for(i=0; i<row; i++){
            for(j=0; j<col; j++){
                for(direct = 0; direct<DIRECT; direct++){ //맵의 행과 열을 다 순회하며, 상하좌우, 대각선의 모든 방향을 체크한다.
                    startRow = i, startCol = j, t = 0; //시작위치 저장과 찾고자 하는 단어의 인덱스 초기화.
                    while(startRow>=0 && startRow<row && startCol>=0 && startCol<col
                    && word[t]!='\0' && (key == 0 || key == 1)) //단어가 해당 방향에 있는지 찾기 위한 반복문, 다른 문자가 나올 경우 key++, key가 1을 넘기면 반복문 종료.
                    {
						if (word[t]!=waldorf[startRow][startCol])
							key++;
						startRow += dirRow[direct];
                       	startCol += dirCol[direct];
                        t++;
                    }
                    if(word[t]=='\0' && (key == 0 || key == 1)){ //단어를 끝까지 순회하였고, 문자도 두개 이상 다르지 않을 경우 값을 저장한다.
                        answer[k].start_row = i;
						answer[k].start_col = j;
						answer[k++].direct_index = direct;
                    }
					key = 0;
                }
            }
        }
		k--; //마지막에 k++로 끝났기때문에 수행
		while(k >= 0) //찾은 위치만큼 반복문 순회한다.
		{	
			i = 0;
			startRow = answer[k].start_row, startCol = answer[k].start_col;
			direct = answer[k].direct_index;
            while(startRow>=0 && startRow<row && startCol>=0 && startCol<col && i < 5) //teemo의 문자수가 5개여서 5번만 수행하는데, 맵을 벗어나지 않아야 한다.
            {
                temp[startRow][startCol] = '#'; //찾은 단어는 #으로 바꾼다.
				startRow += dirRow[direct];
                startCol += dirCol[direct];
				i++;
            }
			k--;
		}
		for(i=0;i<row;i++)//결과를 출력해준다.
		{
			for(j=0;j<col;j++)
				printf("%c",temp[i][j]);
			printf("\n");
		}
		if (testCase != 0)
		printf("\n");
    }
    return 0;
}
```
