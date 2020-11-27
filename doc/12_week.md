# 12주차-그래프 알고리즘

## 문제 1

### 문제설명

여러 가구 사이에 전화를 설치하기 위해 전화회사에 작업을 맡겼는데 설치한 전화선의 길이에 비례하여 설치비를 받는다고 한다.<br>
악덕 전화회사에서는 최대한 비용이 많이 들게 하여 많은 돈을 받으려고 할 것이다.<br>
모든 가구를 연결하며 최대의 비용으로 전화회선을 설치할 수 있는 최대신장트리를 구하라.<br>
<br>
입력의 첫째줄에는 가구의 수(20 이하의 정수)를 입력받는다.<br>
인접행렬과 비슷한 개념으로 가구 사이에 설치해야하는 전화선의 길이(10 이하의 정수)를 행렬로 입력받는다.<br>
<br>
출력은 최대신장트리를 구해서 가중치의 합을 구한다.<br>
<br>
### 실행 화면 예시

<img src="/img/12-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
#include <stdbool.h>
#define INF -12345 //최대신장이므로 작은값을 사용한다.

bool visited[20] = {};
int dist[20] = {};

int get_max_vertex(int n) {
	int v;
	for (int i = 0; i < n; i++) {
		if (visited[i] == false) { //방문을 하지 않은 인덱스가 있는지 찾아내고 v에 저장
			v = i;
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (visited[i] == false && (dist[i] > dist[v])) { //방문하지 않으면서 더 큰 값이 존재하면
			v = i; //큰 값 인덱스를 저장해준다.
		}
	}
	return v;
}

int prim(int map[][20], int start, int n) 
{
	int result = 0;
	for (int u = 0; u < n; u++) {
		dist[u] = INF;
		visited[u] = false;
	}
	dist[start] = 0;
	// 위의 과정은 초기화와, 첫 시작 부분 dist 값을 0으로 초기화하는 것.

	// 아래 for문부터 이제 탐색이 시작되고,
	for (int i = 0; i < n; i++) {
		// 일단 dist[] 값이 가장 작은 값을 탐색한다. (다음으로 가기 위함.)
		// 첫번째는 당연히 0으로 초기화된 start node이다.
		int u = get_max_vertex(n);
		visited[u] = true; // 방문이 이루어진 다음에는 true로 방문을 체크한다.

		if (dist[u] == INF) return (-1); // 만약 그렇게 찾아낸 node의 dist 값이 INF면 종료(동 떨어진 노드)

	//	유효한 값이므로 result에 합산
		result += dist[u];
		// 방문이 끝난 다음에는 dist 값을 새로 방문한 node 기준으로 다시 초기화해줘야 한다.
		for (int v = 0; v < n; v++) {
			if (map[u][v] != INF) { // 전체를 탐색하며 u로부터 v로 가는 길이 연결되어 있다면,
				if (visited[v] == false && map[u][v] > dist[v]) { // 아직 방문하지 않았고, 원래의 dist보다 크다면
					dist[v] = map[u][v]; // 초기화 해준다.
				}
			}
		}
	}
	return result;
}


int main()
{
	int map[20][20];
	int v,row,col,k;
	char buf[1024];
	while (scanf("%d",&v)!=EOF)
	{
		getchar();
		for (row=0;row<v;row++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for (col=0;col<v;col++)
			{
				if (buf[k]-'0' != 0)
					map[row][col] = buf[k]-'0';
				else
					map[row][col] = INF;
				k += 2;
			}
		}
		printf("%d\n",prim(map,0,v)); //결과 출력
	}
}

```

## 문제 2

### 문제설명

다익스트라(Dijkstra) 알고리즘이란 단일 시작점 최단경로 알고리즘으로, 시작 정점에서부터 다른 정점까지의 최단 거리를 구하는 알고리즘이다. <br>
이 알고리즘을 이용하여 주어진 출발점과 어느 한 정점을 지나 도착점에 도달하는 최단거리를 구하는 프로그램을 작성하라.<br>
제일 먼저 테스트 케이스의 개수(T<=5)를 입력받는다. 그다음 노드의 개수 N(3<=N<=20)과 간선의 개수 E(1<=E<=100)를 입력받는다. 그 다음 E 줄에 걸쳐 연결된 간선과 그 간선의 가중치(<=100)를 입력받는다. 여기서 가중치란 비용으로 인식하여 가중치가 적을수록 비용이 적게 드는 것이다.
마지막 줄에는 출발점 S, 꼭 지나야하는 정점 A, 그리고 도착점 F를 차례로 입력받는다.<br>
위의 입력을 바탕으로 어느 한 정점을 꼭 지나 출발점과 도착점 사이의 최단 경로 비용을 출력하는 프로그램을 작성하라. 경로비용은 경로상의 모든 간선들의 가중치의 합이고, 최단경로는 경로비용이 가장 작은 경로이다. 경로가 존재하지 않으면 -1을 출력하라. 단, 지났던 정점을 다시 지나갈 수 있다.<br>
<br>
### 실행 화면 예시

<img src="/img/12-2.png" width="60%" height="60%">

### 코드
```c
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

```

## 문제 3

### 문제설명

시장에 버섯을 팔아 돈을 버는 Teemo는 오늘도 버섯을 채집하기 위해 산에 오른다.<br>
하지만 무서운 늑대가 산에 존재하기 때문에 날이 저물기 전에 산에서 내려오려고 한다.<br>
Teemo는 산의 지도를 보면서 자신이 가장 높이 올라 갔다가 내려올 수 있는 위치를 알아내고 싶다.<br>
<br>
Teemo의 집은 지도의 좌상단인(0,0)에 위치해 있다.<br>
산의 높이는 A-Z로 표현되어 있고 0-25까지의 높이를 의미한다.<br>
Teemo는 인접한 좌표이면 상하좌우, 대각선 어디로든지 이동할 수 있다.<br>
<br>
낮은 곳에서 높은 곳으로 이동할 때는 높이 차이의 제곱만큼의 시간이 걸리지만 높은 곳에서 낮은 곳으로 이동할때는 1시간만 걸린다. 높이가 동일한 곳으로의 이동 시간은 0이라고 가정한다.<br>
* A에서 C로 이동하려면 4시간(A->C는 2만큼 차이가 나고 2를 제곱하면 4가 됨), C에서 A로 이동할 때는 1시간(C->A로 내려오는 것이므로)이 걸린다.<br>
단, 높이 차이가 너무 큰 곳은 올라갈 수도 내려갈 수도 없다.<br>
<br>
산의 크기와 지도, 날이 저물기까지 남은 시간, 넘을 수 있는 최대 높이가 주어질 때<br>
Teemo가 다녀올 수 있는 가장 높은 곳의 높이를 출력하라. (Z가 가장 높은 곳이라면 25가 된다.)<br>

* Teemo는 집에서 출발해서 집으로 돌아 와야 한다.<br>
* 입력 첫 줄은 [가로 X, 세로 Y, 한 번에 오르거나 내려 올 수 있는 최대 높이 H, 날이 저물기까지 남은 시간 T]이다. 여기에서 X와 Y는 10 이하의 정수이고, H는 25 이하의 정수이며, T는 100 이하의 정수이다.<br>
* 다음 줄 부터는 X행 Y열 크기의 지도 행렬이 주어진다.<br>

<br>
단, 입력은 한 개 이상의 테스트케이스가 아래와 같이 반복해서 나올 수 있다.<br>

### 실행 화면 예시

<img src="/img/12-3.png" width="60%" height="60%">

### 코드
```c
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

```
