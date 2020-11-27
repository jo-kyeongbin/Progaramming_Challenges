#include <stdio.h>
#define ABS(x) (((x)<0)?-(x):(x))
//테스트케이스 3번에 대해 통과하지 못한 소스.
//여러 방향에 대해서 고려하지 않고 가중치가 작은 방향으로만 가는 것을 고려해서 문제가 됐다.
//다익스트라로 접근해서 해결하면 되는데, 해결하지 못하였다.
typedef struct highest{
	int x;
	int y;
	int time;
} highest;

int H,T;
int row,col;
int h,t;
int visited[10][10]; //방문여부를 알려주는 변수
highest save[100]; //하산할 때의 가중치를 조절하기 위해 경로 저장.
int try;
int backup;


void init_visit() //방문 초기화
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			visited[i][j] = 0;
}

int go_index(int map[][10] ,int x, int y, int *l) //등산하는 코스 중 가중치가 가장 작은 곳을 택함
{
	int min = 26;
	int c = map[x][y];
	if (x-1>=0 && visited[x-1][y] == 0) //좌
	{
		if(min > map[x-1][y] && c <= map[x-1][y] && map[x-1][y] - c <= H)
		{ //최소값보다 작으면서, 현재위치보다 높은 곳이면서, 올라갈 수 있는 최대 높이를 넘지않는 조건문
			min = map[x-1][y];
			l[0] = x-1; //해당 인덱스를 함수 내에서 쓰기 위해서 저장
			l[1] = y;
		}
	}
	if (x+1<row && visited[x+1][y] == 0) //우
	{
		if (min > map[x+1][y] && c <= map[x+1][y] && map[x+1][y] - c <= H)
		{
			min = map[x+1][y];
			l[0] = x+1;
			l[1] = y;
		}
	}
	if (y-1>=0 && visited[x][y-1] == 0) //상
	{
		if (min > map[x][y-1] && c <= map[x][y-1] && map[x][y-1] - c <= H)
		{
			min = map[x][y-1];
			l[0] = x;
			l[1] = y-1;
		}
	}
	if (y+1<col && visited[x][y+1] == 0) //하
	{
		if (min > map[x][y+1] && c <= map[x][y+1] && map[x][y+1] - c <= H)
		{
			min = map[x][y+1];
			l[0] = x;
			l[1] = y+1;
		}
	}
	if (x+1<row && y-1>=0 && visited[x+1][y-1] == 0) //우상단 대각선
	{
		if (min > map[x+1][y-1] && c <= map[x+1][y-1] && map[x+1][y-1] - c <= H)
		{
			min = map[x+1][y-1];
			l[0] = x+1;
			l[1] = y-1;
		}
	}
	if (x+1<row && y+1<col && visited[x+1][y+1] == 0) //우하단 대각선
	{
		if (min > map[x+1][y+1] && c <= map[x+1][y+1] && map[x+1][y+1] - c <= H)
		{
			min = map[x+1][y+1];
			l[0] = x+1;
			l[1] = y+1;
		}
	}
	if (x-1>=0 && y-1>=0 && visited[x-1][y-1] == 0) //좌상단 대각선
	{
		if (min > map[x-1][y-1] && c <= map[x-1][y-1] && map[x-1][y-1] - c <= H)
		{
			min = map[x-1][y-1];
			l[0] = x-1;
			l[1] = y-1;
		}
	}
	if (x-1>=0 && y+1<col && visited[x-1][y+1] == 0) //좌하단 대각선
	{
		if (min > map[x-1][y+1] && c <= map[x-1][y+1] && map[x-1][y+1] - c <= H)
		{
			min = map[x-1][y+1];
			l[0] = x-1;
			l[1] = y+1;
		}
	}
	if (min == 26) //해당 값이 없다면 return 0
		return 0;
	else
		return 1;
}

int back_index(int map[][10],int x, int y, int *l) //집으로 돌아갈 때의 인덱스를 찾아준다.
{
	int min = 26;
	int c = map[x][y];
	if (x-1>=0 && visited[x-1][y] == 0)
	{
		if(map[x-1][y] <= c && ABS(map[x-1][y] - c) <= H && min > map[x-1][y])
		{//현재 위치보다 낮으면서, 내려갈 수 있는 최대 높이를 지키면서, 최소값을 찾는 조건문
			min = map[x-1][y];
			l[0] = x-1;
			l[1] = y;
		}
	}
	if (x+1<row && visited[x+1][y] == 0)
	{
		if(map[x+1][y] <= c && ABS(map[x+1][y] - c) <= H && min > map[x+1][y])
		{
			min = map[x+1][y];
			l[0] = x+1;
			l[1] = y;
		}
	}
	if (y-1>=0 && visited[x][y-1] == 0)
	{
		if(map[x][y-1] <= c && ABS(map[x][y-1] - c) <= H && min > map[x][y-1])
		{
			min = map[x][y-1];
			l[0] = x;
			l[1] = y-1;
		}
	}
	if (y+1<col && visited[x][y+1] == 0)
	{
		if(map[x][y+1] <= c && ABS(map[x][y+1] - c) <= H && min > map[x][y+1])
		{
			min = map[x][y+1];
			l[0] = x;
			l[1] = y+1;
		}
	}
	if (x+1<row && y-1>=0 && visited[x+1][y-1] == 0)
	{
		if(map[x+1][y-1] <= c && ABS(map[x+1][y-1] - c) <= H && min > map[x+1][y-1])
		{
			min = map[x+1][y-1];
			l[0] = x+1;
			l[1] = y-1;
		}
	}
	if (x+1<row && y+1<col && visited[x+1][y+1] == 0)
	{
		if(map[x+1][y+1] <= c && ABS(map[x+1][y+1] - c) <= H && min > map[x+1][y+1])
		{
			min = map[x+1][y+1];
			l[0] = x+1;
			l[1] = y+1;
		}
	}
	if (x-1>=0 && y-1>=0 && visited[x-1][y-1] == 0)
	{
		if(map[x-1][y-1] <= c && ABS(map[x-1][y-1] - c) <= H && min > map[x-1][y-1])
		{
			min = map[x-1][y-1];
			l[0] = x-1;
			l[1] = y-1;
		}
	}
	if (x-1>=0 && y+1<col && visited[x-1][y+1] == 0)
	{
		if(map[x-1][y+1] <= c && ABS(map[x-1][y+1] - c) <= H && min > map[x-1][y+1])
		{
			min = map[x-1][y+1];
			l[0] = x-1;
			l[1] = y+1;
		}
	}
	if (min == 26) //그러한 값이 존재하지 않다면 return 0
		return 0;
	else
		return 1;
}

int go_home(int map[][10],int x, int y) //집으로 돌아갈 때 시간을 누적시켜주는 함수
{
	int l[2];
	int diff;
	visited[x][y] = 1;
	if (x < 0 || y < 0 || x >= row || y >= col || t > T) return 0; //인덱스 범위 예외처리, 시간 초과 예외처리
	if (x == 0 && y == 0) return 1; //집에 도달했다면 return 1
	if (back_index(map,x,y,l)==1)
	{
		diff = map[x][y] - map[l[0]][l[1]]; //높은 곳 - 낮은 곳 > 0
		if (diff != 0) //back_index에서 예외처리 해주었지만 한번 더 예외처리
		{
			t += 1;
			backup += 1; //잘못됐다면 시간을 다시 빼주기 위해 누적
		}
		if(go_home(map,l[0],l[1])==1) return 1; //return 1이 되면 재귀호출했던 것들이 전부 return 1이 된다.
	}
	return 0;
}

void find(int map[][10] ,int x, int y) //최고로 높은 곳을 가면서 시간 누적과 경로를 저장해주는 함수
{
	int l[2];
	int diff;
	int time;
	visited[x][y] = 1; //해당 좌표를 방문한 것으로 설정
	if (x < 0 || y < 0 || x >= row || y >= col || t > T)  //인덱스 예외처리와 시간 예외 처리
	{
		try--; //예외였으므로 try--를 해준다. try는 경로의 수이다. save의 index를 위한 변수
		return ;
	}
	if(go_index(map,x,y,l)==1) //유효한 index를 찾았다면
	{
		save[try%100].x = l[0]; save[try%100].y = l[1]; //해당 좌표를 저장
		diff = map[l[0]][l[1]] - map[x][y]; //해당 좌표와 현재 좌표의 차이를 구해서
		time = diff * diff; //등산 시간을 구한다.
		save[try%100].time = time; //시간을 저장한다.
		t += time; //시간을 누적한다.
		try++; //다음 save를 위해 index 증가
		find(map,l[0],l[1]); //다음 좌표에서의 재귀호출
	}
	else //모두 방문하여서 유효한 인덱스가 존재하지 않다면 재귀가 종료되는 부분
	{	
		try--; //인덱스를 감소하고 함수를 종료시킨다.
		return ;
	}
}

int main()
{
	int map[10][10];
	int i,j;
	char buf[1024];

	while (scanf("%d %d %d %d",&row,&col,&H,&T)!=EOF)
	{
		getchar();
		for (i=0;i<row;i++)
		{
			fgets(buf,1024,stdin);
			for (j=0;j<col;j++)
				map[i][j] = buf[j]-'A';
		}
		try = 0;
		t = 0;
		init_visit();
		find(map,0,0); //우선 등산 경로를 탐색하고,
		while (try>0)
		{
			backup = 0;
			init_visit(); //방문을 초기화한다.
			if(go_home(map,save[try%100].x,save[try%100].y)==1) break; //집에 도달하였다면 반복문 종료.
			t -= save[try%100].time; //그렇지 않다면 마지막 방문해서 소요된 시간을 차감.
			t -= backup; //마찬가지로 집에 돌아가면서 누적했던 시간들 차감.
			try--; //이전 값을 불러오기 위해 try--
		}
		printf("%d\n",map[save[try%100].x][save[try%100].y]); //무사히 집에 도달했을 때의 최고점을 출력
	}
}
