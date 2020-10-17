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

<img src="/img/1-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

#define BUFSIZE 1024

int main(void)
{
    char line[BUFSIZE];

    while (fgets(line, BUFSIZE, stdin) != NULL) {
        if (line[0] == '0') { //0으로 시작하면 16진수를 의미한다.
            int hex = 0;
            sscanf(line + 2, "%x", &hex); //sscanf를 통하여 문자열을 16진수로 바꾼다. line+2를 하는 이유는 0x부분을 건너뛴 숫자부분만 필요하기 때문이다.
            printf("%d\n", hex); 			//%d를 통하여 16진수를 10진수로 변경하였다.
        }
        else {	//10진수일 경우
            int dec = 0;
            sscanf(line, "%d", &dec);	//마찬가지로 문자열을 int로 변경.
            printf("0x%X\n", dec);		//%X로 16진수 형태로 표현해준다.
        }
    }
    return 0;
}
```

## 문제 1-3 : "3n+1 문제" 변형

### 문제설명
짝수면 2로 나누고, 홀수면 3을 곱한 다음 1을 더하는 방식으로 수열을 만들 수 있다. 어떤 숫자로 시작하든지, 이 수열에 언젠가는 1이 등장한다고 수학자들은 추측하고 있다. 예를 들어 n=22라면
22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1
이런 수열이 만들어진다.<br><br>
숫자 두 개가 있을 때, 첫번째 숫자로 시작한 수열에 두 번째 숫자가 포함되는지를 판단해 포함되면 Y, 그렇지 않으면 N을 출력하라.

### 실행 화면 예시

<img src="/img/1-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int cyclehas(int n, int x)
{
    if (n == x) return 1;	//x가 해당 수열에 존재하면 1을 리턴해주는 함수이다.
    while (n != 1) {	//n이 1이 될때까지
        if (n % 2 == 0) n /= 2;	//짝수이면 2로 나누고,
        else n = 3*n + 1;	//홀수이면 3n+1을 수행한다.
        if (n == x) return 1;
    }
    return 0;	//해당 수열에 존재하지 않으면 0을 리턴한다.
}

int main(void)
{
    int n, x;

    while (scanf("%d %d", &n, &x) == 2) {
        if (cyclehas(n, x)) printf("Y\n");	//1을 리턴하여 참이면 Y
        else printf("N\n");	//아니면 N을 리턴한다.
    }
    return 0;
}

```
