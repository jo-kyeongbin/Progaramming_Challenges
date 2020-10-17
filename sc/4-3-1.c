#include <stdio.h>

#define M 50
#define N 50
#define BUFFERSIZE 1024
#define DIRECT 8

typedef struct result{
	int direct_index;
	int start_row;
	int start_col;
}result;

int main() {
    char waldorf[M][N];
	char temp[M][N];
    int testCase, row, col, i, j, k, len, startRow, startCol, direct, t, key=0;
    char inputDivision[BUFFERSIZE];
	char word[6] = "teemo";

    int dirRow[DIRECT] = {-1,-1,-1,0,1,1,1,0};
    int dirCol[DIRECT] = {-1,0,1,1,1,0,-1,-1};
	result answer[300];

    scanf("%d",&testCase);
    gets(inputDivision);
    while(testCase--){
		gets(inputDivision);
        scanf("%d %d",&row, &col);
        gets(inputDivision);
        for(i=0; i<row; i++){
            for(j=0; j<col; j++){
                waldorf[i][j] = getchar();
				temp[i][j] = waldorf[i][j];
                if(waldorf[i][j] >= 'A' && waldorf[i][j] <= 'Z'){
                    waldorf[i][j] += ('a' - 'A');
                }
            }
            gets(inputDivision);
        }
		k = 0;
        for(i=0; i<row; i++){
            for(j=0; j<col; j++){
                for(direct = 0; direct<DIRECT; direct++){
                    startRow = i, startCol = j, t = 0;
                    while(startRow>=0 && startRow<row && startCol>=0 && startCol<col
                    && word[t]!='\0' && (key == 0 || key == 1))
                    {
						if (word[t]!=waldorf[startRow][startCol])
							key++;
						startRow += dirRow[direct];
                       	startCol += dirCol[direct];
                        t++;
                    }
                    if(word[t]=='\0' && (key == 0 || key == 1)){
                        answer[k].start_row = i;
						answer[k].start_col = j;
						answer[k++].direct_index = direct;
                    }
					key = 0;
                }
            }
        }
		k--;
		while(k >= 0)
		{	
			i = 0;
			startRow = answer[k].start_row, startCol = answer[k].start_col;
			direct = answer[k].direct_index;
            while(startRow>=0 && startRow<row && startCol>=0 && startCol<col && i < 5)
            {
                temp[startRow][startCol] = '#';
				startRow += dirRow[direct];
                startCol += dirCol[direct];
				i++;
            }
			k--;
		}
		for(i=0;i<row;i++)
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