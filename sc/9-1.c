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