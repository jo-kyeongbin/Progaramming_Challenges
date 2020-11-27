#include <stdio.h>
#define ABS(x)  (((x)<0)?-(x):(x))

int N;
int board[10];

int possible(int row) {
    for (int i = 0; i < row; i++) {
        if (board[i] == board[row] || (row - i) == ABS(board[i] - board[row])) {
            return 0;
        }
    }
    return 1;
}

void setQueen(int row) {
    int i;
    int j;
    if (row == N) {
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
    else {
        for (int col = 0; col < N; col++) {
            board[row] = col;

            if (possible(row)) {
                setQueen(row + 1);
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