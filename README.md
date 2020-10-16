# Progaramming_Challenges


> 문제해결프로그래밍 실습 시간에 다루었던 소스 코드를 기반으로 복습차원으로 주석을 추가하였습니다.<br>
교재는 [**Programming Challenges**](http://www.programming-challenges.com)를 사용합니다.<br>
__본 문제들은 교재에 없으며, 교재 문제 응용 문제로 공부에 많은 도움이 됩니다.__


# 1주차

## 문제 1-1 : 글자 세리기

### 문제설명

> 입력 각 줄에 있는 단어 수와 (공백을 제외한) 글자 수를 세어 출력하라. 한 줄에는 공백 포함 최대 1024글자가 있고, 단어는 공백으로 분리되어 있다. 몇 줄이 들어올지는 미리 알 수 없으므로 EOF를 체크해야 한다.<br>
예를 들어 아래 예제처럼 2줄이 입력되면 2줄에 대해 각각 글자수와 단어수를 두번씩 출력해야 한다.

### 실행 화면 예시

<img src="/img/1-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

#define BUFSIZE 1024

int main(void)
{
    char line[BUFSIZE];

    while (fgets(line, BUFSIZE, stdin) != NULL) {
        int words = 0, letters = 0;
        int i = 0;
        while (line[i] != '\n') {
            if ((i == 0 && line[i] != ' ') ||
                (i > 0 && line[i-1] == ' ' && line[i] != ' ')) //단어의 수는 공백을 기준으로 나눕니다.
                words++;
            if (line[i] != ' ') letters++; //문자의 수는 공백이 아닌 것을 기준으로 나눕니다.
            i++;
        }
        printf("%d %d\n", words, letters);
    }
    return 0;
}
```

## 문제 1-2 : 10진수 대 16진수

### 문제설명

> 10진수는 평범하게 표기하고, 16진수는 앞에 0x를 붙여서 표기한다. 각 줄에는 10진수 혹은 16진수 숫자가 씌여 있다.<br>
10진수는 16진수로 바꾸고, 16진수는 10진수로 바꾸라. 모든 숫자는 양의 숫자이다 (0이나 음수 없음).

*16진수에서 ABCDE는 모두 대문자로 입출력.

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
        if (line[0] == '0') {
            int hex = 0;
            sscanf(line + 2, "%x", &hex); // Skip first two characters ("0x")
            printf("%d\n", hex);
        }
        else {
            int dec = 0;
            sscanf(line, "%d", &dec);
            printf("0x%X\n", dec);
        }
    }
    return 0;
}
```

## 문제 1-3 : "3n+1 문제" 변형

### 문제설명
> 짝수면 2로 나누고, 홀수면 3을 곱한 다음 1을 더하는 방식으로 수열을 만들 수 있다. 어떤 숫자로 시작하든지, 이 수열에 언젠가는 1이 등장한다고 수학자들은 추측하고 있다. 예를 들어 n=22라면
22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1
이런 수열이 만들어진다.<br><br>
숫자 두 개가 있을 때, 첫번째 숫자로 시작한 수열에 두 번째 숫자가 포함되는지를 판단해 포함되면 Y, 그렇지 않으면 N을 출력하라.

### 실행 화면 예시

<img src="/img/1-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int cyclehas(int n, int x)
{
    if (n == x) return 1;
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3*n + 1;
        if (n == x) return 1;
    }
    return 0;
}

int main(void)
{
    int n, x;

    while (scanf("%d %d", &n, &x) == 2) {
        if (cyclehas(n, x)) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
```

