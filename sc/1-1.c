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