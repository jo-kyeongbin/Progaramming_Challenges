# 2주차

## 문제 1

### 문제설명

> 알파벳으로만 이루어진 계산기가 있다. <br>
A는 0, B는 1...J는 9를 뜻하며 P는 더하기, S는 빼기, T는 곱하기, V는 나누기를 뜻한다. 다른 문자는 입력되지 않는다.<br>
예를 들어, "BDAPCC"는 130+22를 의미한다.<br>
이 계산기는 입력된 순서대로 연산을 진행하며 수식이 올바르지 못한 경우 오류가 발생한다.<br>
예를 들어, "BPCSDTEVF"는 2+3-4*5/6을 의미하는데, 여기서 우리가 알던 연산자 우선순위를 적용하지 않고 입력된 순서<br>
즉, +, -, *, / 순서로 연산이 진행되며, "PTV"처럼 연산자와 피연산자가 적절히 대응하지 않는 경우 오류가 발생한다.<br>
입력된 문장의 계산 결과를 출력하라. 계산 과정에서 모든 결과값은 int 범위를 벗어나지 않는다. 오류가 난 경우에는 "Error"를 출력한다.<br>

### 실행 화면 예시

<img src="/img/2-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#define BUFSIZE 1024

int main() {
	int i;
	int temp;
	int temp2;
	int key;
	char cal;
	char n[BUFSIZE];
	
	while (fgets(n, BUFSIZE, stdin)!=NULL){
		if (!('A' <= n[0] && 'J' >= n[0]))	//주어진 문자가 아닐 경우에 error를 출력한다.
		{
			printf("Error\n");
			continue;
		}
		i = 0;
		temp = 0;
		key = 0;
		while (n[i])
		{
			if ('A' <= n[i] && n[i] <= 'J' && key == 0) //key를 두어서 연산자와 피연산자를 구분하였다.
			{
				temp = temp * 10 + (n[i++] - 65); //65는 대문자 A의 아스키코드이며, 65를 빼면 숫자가 된다.
				continue;
			}
			else if (!('A' <= n[i] && n[i] <= 'J') && n[i] != '\n') //만약에 연산자라면, \n은 fgets 특성상 개행도 읽기 때문이다.
			{
				if (!('A' <= n[i - 1] && n[i - 1] <= 'J')) // 앞에 연산자가 나왔는데 전에 온 문자가 피연산자가 아니라면 에러.
				{
					printf("Error\n");
					key = -1; //에러가 발생하면 와일문을 종료한다. 그리고 밑에서 출력을 방지해주기 위해 key를 -1로 둔다.
					break;
				}
				key = 1;	//key 값이 1이기 때문에 temp의 값이 변하지 않는다.
				cal = n[i++];	//연산자를 저장해준다.
				if (n[i] == '\n')	//앞에서 i++을 했기에 \n일수도 있고, 연산자 이후 피연산자가 나오지 않았으므로 에러처리
				{
					printf("Error\n");
					key = -1;
				}
				temp2 = 0;
				continue;	//다시 while문 수행하면 아래에서 temp2 초기화를 시작한다. (temp1 연산자 temp2 순서)
			}
			else if (key == 1 && ('A' <= n[i] && n[i] <= 'J'))
			{
				temp2 = temp2 * 10 + (n[i++] - 65);
				if (!('A' <= n[i] && n[i] <= 'J')) //i++을 해주었기 때문에 연산자일수도 있다. 연산자라면 연산을 수행한다.
				{
					if (cal == 'S')
						temp = temp - temp2;
					if (cal == 'T')
						temp = temp * temp2;
					if (cal == 'V')
					{
						if (temp2 == 0) //0으로 나누는 경우는 에러처리 한다.
						{
							printf("Error\n");
							key = -1;
							break;
						}
						temp = temp / temp2;
					}
					if (cal == 'P')
						temp = temp + temp2;
				} //temp의 값이 temp2와 연산을 수행한 결과로 바뀌게 된다. (계속 누적된다.)
				continue;
			}
			if (n[i] == '\n') //while문은 \n가 나오거나 널문자가 나오면 종료된다.
				break;
		}
	if (key != -1)
		printf("%d\n",temp); //에러가 나온 경우가 아니라면 temp의 값을 출력해준다.
	}
}
```

## 문제 2

### 문제설명

> Tom과 Jerry 두 사람이 각각 A부터 Z까지 섞여있는 카드뭉치에서 카드를 5장 뽑아 서로 우위를 점한다.<br>

포카드 : 같은 카드가 4장<br>
트리플 : 같은 카드가 3장<br>
페어 : 같은 카드가 2장<br>

포카드 > 트리플 > 페어 순으로 등급이 높으며 두 사람이 같은 등급일 경우 B가 A보다 높다.<br>

*예를 들면 A포카드는 Z트리플보다 높고, Z트리플은 C트리플보다 높다.<br>

카드뭉치에서 같은 알파벳의 카드는 4장까지 있으므로 서로 같은 등급의 트리플 혹은 포카드를 가지는 경우는 당연히 없다.<br>
또한 한 명이 AABBC와 같이 A페어, B페어를 가지는 경우 더 높은 B페어가 등급이 되며<br>
서로 같은 등급의 페어를 가지는 경우 무승부가 된다.<br>

Tom과 Jerry 순서대로 두 사람의 패가 주어질 때 누가 승자인지 승자의 이름을 출력하여라. 무승부인 경우 Draw를 출력하라.<br>

* 포카드, 트리플, 페어 이외의 다른 룰은 적용하지 않는다.<br>
<br>
*16진수에서 ABCDE는 모두 대문자로 입출력.<br>

### 실행 화면 예시

<img src="/img/2-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#include <stdlib.h>

char* cmp_card(char *a)
{
	int count = 0;
	char *temp;
	int i,j;

	temp = (char*)malloc(sizeof(char) * 2);
	for (i=0;i<5;i++) // 앞에서부터 하나씩 비교해가면서 다음에 나올 문자가 현재와 같은 문자가 나오면 count를 증가시켜준다.
	{
		for (j=i+1;j<5;j++)
		{
			if (a[i] == a[j])
				count++;
		}
		if (temp[1] < (count + '0') || (temp[1] == (count + '0') && temp[0] < a[i]) || i == 0) //초기값이거나 더 큰 숫자를 가지거나, 같은 숫자인데 더 높은 알파벳을 가지면 temp에 저장한다.
		{
			temp[0] = a[i];
			temp[1] = count + '0';
		}
		count = 0;
	}
	return temp;
}

int main(){
	char input[12];
	char temp[5];
	char *value1;
	char *value2;
	int i;

	while (fgets(input, 12, stdin) != NULL)
	{
		for(i = 0 ;i < 5;i++)
			temp[i] = input[i]; //앞에 다섯장을 입력받는다.
		value1 = cmp_card(temp);
		for(i = 0;i < 5;i++)
			temp[i] = input[i+6]; //뒤에 다섯장을 입력받는다.
		value2 = cmp_card(temp);
		if (value1[1] > value2[1] || (value1[1] == value2[1] && value1[0] > value2[0])) //왼쪽(Tom)이 이기는 경우
			printf("Tom\n");
		else if (value1[1] < value2[1] || (value1[1] == value2[1] && value1[0] < value2[0])) //오른쪽(Jerry)가 이기는 경우
			printf("Jerry\n");
		else
			printf("Draw\n");
		getchar(); //버퍼를 비워주기 위해 수행, 수행하지 않으면 printf가 두번씩 수행된다.
		free(value1);
		free(value2);
	}
}
```

## 문제 3

### 문제설명
> bigram이란 알파벳 두 글자로 이루어진 패턴을 의미한다.<br>
예를 들어, I have a hat 이란 문장에는 ha, av, ve, at 이렇게 네가지의 bigram이 있다 (ha는 두 번 등장). 등장하는 bigram의 빈도수를 파악하여 가장 많이 등장하는 bigram을 출력하자.<br>
단, 2회 이상 등장하는 bigram이 없으면 Not present를 출력한다. 입력 각 줄에는 공백 포함 최대 10000글자가 있다.<br>
* 대소문자 구분<br>
* 영문 알파벳이 아닌 문자 무시 (bigram에 포함하지 않음)<br>
* 가장 많이 등장하는 bigram이 2개 이상일 경우 ascii 순으로 정렬하여 출력<br>
* ascii 순이란 A..Z가 먼저 오고 그 다음 a..z가 온다는 뜻<br>

### 실행 화면 예시

<img src="/img/1-2.png" width="60%" height="60%">

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
