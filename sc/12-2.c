#include <stdio.h>
#include <stdbool.h>
#define NONE 333

bool visit[20] = {}; //노드의 방문 여부
int d[20] = {}; //다익스트라 힘수의 경로비용 누적

void init_visit() //방문 초기화 함수
{
	for(int i=0;i<20;i++)
		visit[i] = false;
}

void add_map(int map[][20], int x, int y, int value) //방향성이 없는 가중치 그래프
{
	map[x][y] = value;
	map[y][x] = value;
}

void init_map(int map[][20]) //맵 초기화 함수
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
				map[i][j] = NONE;
	}
}

int getSmallIndex(int v) { // 방문하지 않으면서 가중치가 작은 인덱스를 리턴한다.
	int min = NONE;
	int index = 0;
	for (int i =0; i < v; i++) {
		if(d[i] < min && !visit[i]) {
			min = d[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(int map[][20] ,int start, int v){
	for(int i =0; i < v; i++) { //초기값으로 같은 행의 값들 저장
		d[i] = map[start][i];
	}
	visit[start] = true; //시작 지점을 방문한 것으로 함.
	for(int i =0; i < v; i++) { //v-2번만 수행해도 된다.
		int current = getSmallIndex(v); //가중치가 작은 인덱스를 저장
		visit[current] = true; //가중치가 작은 인덱스를 방문한 것으로 두고,
		for(int j=0; j < v; j++) { //직행해서 j로 가는 것보다 current를 들려서 j로 가는 것의 비용이
				if(d[current]+map[current][j] < d[j]) { //더 작다면, 경유한 값을 d[j]에 저장.
					d[j] = d[current]+map[current][j];
				}
		}
	}
}

int main()
{
	int map[20][20];
	int tcase;
	int result1,result2; //result1은 처음-중간까지의 경로비용, result2는 중간-끝까지의 경로비용 저장
	int v,e;
	int start,mid,end;
	int x,y,value;

	while (scanf("%d",&tcase)!=EOF)
	{
		getchar();
		while (tcase>0)
		{
			scanf("%d %d",&v,&e);
			getchar();
			init_map(map);
			init_visit();
			while (e>0)
			{
				scanf("%d %d %d",&x,&y,&value);
				getchar();
				add_map(map,x-1,y-1,value);
				e--;
			}
			scanf("%d %d %d",&start,&mid,&end);
			getchar();
			dijkstra(map,start-1,v); //시작점부터의 다익스트라 함수
			result1 = d[mid-1]; //중간지점까지의 경로비용 저장
			init_visit(); //방문기록 초기화
			dijkstra(map,mid-1,v); //중간지점부터의 다익스트라 함수
			result2 = d[end-1]; //끝지점까지의 경로비용 저장
			if (result1 == NONE || result2 == NONE) //시작-중간 혹은 중간-끝으로 가는 길이 없으면 -1 출력
				printf("-1\n");
			else
				printf("%d\n",result1+result2); //그렇지않으면 처음-중간-끝지점의 경로비용 출력
			tcase--;
		}
	}
}
