# Progaramming_Challenges


문제해결프로그래밍 실습 시간에 다루었던 소스 코드를 기반으로 복습차원으로 주석을 추가하였습니다.

교재는 [**Programming Challenges**](http://www.programming-challenges.com)를 사용합니다.


## 문제 1-1 : 글자 세리기

### 문제설명

입력 각 줄에 있는 단어 수와 (공백을 제외한) 글자 수를 세어 출력하라. 한 줄에는 공백 포함 최대 1024글자가 있고, 단어는 공백으로 분리되어 있다. 몇 줄이 들어올지는 미리 알 수 없으므로 EOF를 체크해야 한다. 예를 들어 아래 예제처럼 2줄이 입력되면 2줄에 대해 각각 글자수와 단어수를 두번씩 출력해야 한다.

### 실행 화면 예시

<center><img src="/img/1-1.png" width="60%" height="60%"></center></img>

### 코드
```
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
                (i > 0 && line[i-1] == ' ' && line[i] != ' '))
                words++;
            if (line[i] != ' ') letters++;
            i++;
        }
        printf("%d %d\n", words, letters);
    }
    return 0;
}
```
