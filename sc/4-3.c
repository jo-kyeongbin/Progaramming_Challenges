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