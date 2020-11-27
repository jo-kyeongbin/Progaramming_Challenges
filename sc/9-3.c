#include <stdio.h>

int count;
int row, col; //행, 열
int map[10][10]; //맵

const int PATHWAY = 1; //갈 수 있는 곳
const int BLOCKED = 4; //막혀있는 곳
const int PATH = 3; //지나간 곳
const int DST = 2; //목적지

void print_map() //정답(맵)을 출력해주는 함수
{
	int i,j,count;
	count = 0;
	for (i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if (map[i][j]==PATH)
			{
				printf("1 ");
				count++;
			}
			else if(map[i][j] == DST)
			{
				printf("%d ",DST);
				count++;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("%d\n",count); //도착지를 포함한 경로의 수를 출력
}


void find(int i, int j)
{
	if(i<0 || j<0 || i>=row || j>=col) return ; //인덱스를 벗어나는 부분을 예외처리
	else if(map[i][j] != PATHWAY && map[i][j] != 2) return ; //도착지가 아니면서 갈 수 없는 길이면 제외
    else if(map[i][j]==DST) { //목적지에 도달하면 정답 출력
		if (count > 0) //결과가 여러개이면
			printf("\n");
		print_map();
		count++;
    }else {
        map[i][j] = PATH; //해당 길을 지나온 길로 표시
		//문제에서 요구한대로 순회 (우측-하단-좌측-상단)
        find(i, j+1);
		find(i+1, j);
		find(i, j-1);
		find(i-1, j);
	if (map[i][j]==PATH) //dfs로 바로 직전의 결과를 다시 안간 것으로 처리하여 다른 길을 찾아본다.
		map[i][j] = PATHWAY;
    }
}

int main()
{
	int i,j,k;
	char buf[1024];
	while(scanf("%d %d",&row,&col)!=EOF)
	{
		getchar();
		for(i=0;i<row;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<col;j++)
			{
				map[i][j] = buf[k]-'0';
				k+=2; //공백이 존재하여 짝수 인덱스만 맵에 저장.
			}
		}
		count = 0; //출력결과가 여러개이면 공백을 추가하기 위한 변수
   		find(0,0);
	}
}
