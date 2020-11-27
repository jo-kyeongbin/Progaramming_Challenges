# 11주차-그래프 순회

## 문제 1

### 문제설명

N개의 정점과 정점들 사이에 방향성이 없는 에지가 있는 그래프가 주어졌을 때, 인접한 정점들 사이에 색이 중복되지 않도록 색칠하는 방법을 모두 출력하라.<br> 
N은 10 이하의 정수이다. 만약, 인접 정점을 다른색으로 칠하지 못하는 경우에는 NONE을 출력하라.<br> 
예시와 같은 입력을 그래프로 그리면 다음과 같다.<br> 
<br> 
```
     (1)
    /  |
   /   |
  /    | 
(2)--(3) 
```
<br> 
그래프 입력 부분의 첫줄을 살펴보면, 0 1 1인데, 이는 1번 점은 2번점과 3번 점에 연결되어 있음을 나타낸다. <br> 
두번째 줄을 살펴보면, 1 0 1인데, 이는 2번 점은 1번점과 3번 점에 연결되어 있음을 나타낸다.<br> 
<br> 
입력의 첫줄에는 정점의 갯수 N과 칠할 색의 최대 개수 C(1<=C<=3)를 입력받고, 두번째 줄부터는 N*N 크기 정점들사이의 에지를 나타내는 그래프가 입력된다.<br> 
출력은 각 정점들에 몇번 째 색이 칠해졌는지를 출력하며, 모든 경우의 수를 출력하라.<br> 
출력은 정점의 순서대로 1번 정점 2번 정점 3번 정점에 각각 어떤 색을 칠할 수 있는지를 나타내야 한다. 출력이 여러 개일 경우, 낮은 번호의 색이 먼저 오는 경우를 먼저 출력해야 한다.<br> 
아래 예시에서 출력의 첫째 줄을 보면 1 2 3인데, 이는 1번 정점에는 첫번째 색, 2번 정점에는 두번째 색, 3번 정점에는 세번째 색을 칠할 수 있음을 나타낸다.<br> 

### 실행 화면 예시

<img src="/img/11-1.png" width="60%" height="60%">

### 코드
```c
#include <stdbool.h>
#include <stdio.h>

int V;
int key;
void printSolution(int color[]);

bool isSafe(bool graph[10][10], int color[])
{
	for (int i = 0; i < V; i++)
		for (int j = i + 1; j < V; j++)
			if (graph[i][j] && color[j] == color[i]) //그래프가 인접해 있으면서, 색깔이 같으면 false
				return false;
	return true; //해당 경우가 없으면 true
}

bool graphColoring(bool graph[][10], int m, int i,int color[10])
{
	if (i == V) { //재귀함수 종료 부분, i와 정점의 개수가 같다면
		if (isSafe(graph, color)) {
			key = 1; //정답을 출력하였다면 key=1
			printSolution(color); //컬러 출력
		}
		return false;
	}
	for (int j = 1; j <= m; j++) {
		color[i] = j;
		graphColoring(graph, m, i + 1, color); //dfs로 재귀를 호출한다.
		color[i] = 0; //dfs를 위해 다시 초기화
	}
	return false;
}

void printSolution(int color[]) //컬러를 출력해주는 함수
{
    for (int i = 0; i < V-1; i++)
        printf("%d ", color[i]);
    printf("%d \n",color[V-1]);
}

int main()
{
	bool graph[10][10];
    int m;
    int i,j,k;
	char buf[1024];
	while(scanf("%d %d",&V,&m)!=EOF)
	{
		getchar();
		for(i=0;i<V;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<V;j++)
			{
				graph[i][j] = buf[k]-'0';
				k+=2;
			}
		}
		int color[V];
		for (int i = 0; i < V; i++)
			color[i] = 0;
		key = 0;
		graphColoring(graph, m, 0, color);
		if (key == 0) //정답이 없다면
			printf("NONE\n");
	}
	return 0;
}

```

## 문제 2

### 문제설명

보물찾기 지도 제작 의뢰가 들어왔다. 지도에는 1과 0으로 행렬을 그려 맨 윗줄의 첫번째(가장 왼쪽) 1이 출발지점이고, <br>
맨 마지막 줄의 마지막(가장 오른쪽) 1이 도착지점으로 가정한다.<br>
출발지점으로부터 시작해서 도착지점까지의 최단 경로 길이를 너비 우선 탐색 방법을 통해 알아내려고 한다. <br>
인접 1로만 경로가 형성되는데, 대각선으로는 갈 수 없다.<br>
<br>
1로 표시된 좌표들은 모두 연결되어 있다.<br>
<br>
첫 번째로 좌표의 크기를 지정하는 정수를 입력한다. 그 정수는 좌표의 행과 열의 값을 의미한다.<br>
그 다음부터 입력한 정수만큼 좌표를 입력한다. 여기서 1은 지나갈 수 있는 길을 의미하고, 0은 지나갈 수 없는 벽을 의미한다. 단 첫번째 줄은 모두 1이다.<br><br>
주어진 입력에서 최단 경로의 길이를 출력해야 한다. 출발지점과 도착지점을 포함한 1의 개수가 최단 경로의 길이가 된다.<br>
위와 같은 입력과 출력을 갖는 최단 경로 길이를 출력하는 프로그램을 작성하라.<br>
### 실행 화면 예시

<img src="/img/11-2.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int n, count;
int map[10][10];
int x[100], y[100], l[100];

void save(int i, int j, int k) //save()를 통하여 방향을 정한다.
{ 
	x[count] = i; //x좌표 저장
	y[count] = j; //y좌표 저장
	l[count] = k; //경로의 개수를 의미하는 변수
	count++; //save()가 호출될 때마다 증가, 1이 연달아 붙어 있다면 pos보다 항상 큰 값을 가진다.
}

void bfs(int i, int j)
{
	int pos = 0;
	save(i, j, 1); //count가 기본적으로 1을 가진다.

	while (pos < count && (x[pos] != n - 1 || y[pos] != n - 1)) //x와 y가 n,n(끝)에 도달하면 종료
	{ //상하좌우 순서로 맵을 순회하면서 map이 1인 부분을 저장한다.
		map[y[pos]][x[pos]] = 0;//현재 위치를 방문한 것으로 표시한다. 또한 save()로 인하여 방향이 정해짐.
		if (y[pos] > 0 && map[y[pos] - 1][x[pos]] == 1) //상
			save(x[pos], y[pos] - 1, l[pos] + 1);
		if (y[pos] < n - 1 && map[y[pos] + 1][x[pos]] == 1) //하
			save(x[pos], y[pos] + 1, l[pos] + 1);
		if (x[pos] > 0 && map[y[pos]][x[pos] - 1] == 1) //좌
			save(x[pos] - 1, y[pos], l[pos] + 1);
		if (x[pos] < n - 1 && map[y[pos]][x[pos] + 1] == 1) //우
			save(x[pos] + 1, y[pos], l[pos] + 1);
		pos++;
	}
	if (pos < count) //while문을 탈출하였을 경우 경로 수(정답) 출력
		printf("%d\n", l[pos]);
}

int main()
{
	int i,j,k,row,col;
	char buf[1024];
	while(scanf("%d",&n)!=EOF)
	{
		getchar();
		row = n;
		col = n;
		for(i=0;i<row;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<col;j++)
			{
				map[i][j] = buf[k]-'0';
				k+=2;
			}
		}
   		bfs(0,0);
	}
	return 0;
}

```

## 문제 3

### 문제설명

배달부인 철수는 어느 마을에 택배를 배달한다.<br>
마을은 시골 마을이라 큰 길이 없고, 각 집들 간에만 서로 오갈 수 있는 길이 있다.<br>
특정 집에서 시작하여 모든 집들에 배달을 하고 다시 출발점으로 돌아오는 경로를 짜고자 한다.<br>
다음 규칙에 따라 경로를 탐색한다.<br>
<br>
- 모든 집에는 한 번씩만 방문한다.<br>
- 방법의 수만 출력하는 것이 아닌, 경로를 직접 출력한다.<br>
- 모든 집에 배달하고 다시 출발점으로 돌아올 수 있는 경로가 없다면 0을 출력한다.<br>
<br>
첫 번째 줄에는 배달할 집의 수 n, 집들 간 경로의 수 m, 출발점의 위치 k를 공백 기준으로 입력받는다.<br>
그 후 m번 만큼 집과 집 사이를 잇는 길의 정보를 입력받는다.<br>
<br>
단, n, m, k는 다음 조건을 만족한다.<br>
<br>
2 <= n <= 10, 0 <= m <= n * (n - 1) / 2, 1 <= k <= n<br>
<br>
출력할 때에 경로가 여러가지라면 모두 출력한다.<br>
단, 오름차순으로 출력한다. (경로가 1 2 3 1과 1 3 2 1이 있다면 1 2 3 1을 먼저 출력한다.)<br>

### 실행 화면 예시

<img src="/img/11-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h> 

int size; //집의 수
int start; //시작 인덱스
int success, //정답의 존재 여부
    v[10]; //방문한 코스 저장
int visited[11]; //방문했는지의 여부 1 아니면 0
int map[11][11]; // 맵 저장


void add(int s, int e) //방향성 없는 그래프여서 (x,y), (y,x)에 같은 값 입력
{
	map[s][e] = 1;
	map[e][s] = 1;
}

void visit(int i, int r) 
{ 
    int k; 

    if(r==0 && i==start)  //재귀 종료 부분, 모든 경로를 다 돌고, 다시 시작점으로 왔을 경우
    {
		v[r]=i;
        for(k=size;k>0;k--) //v를 역순으로 저장하였기에 역순으로 출력
			printf("%d ",v[k]);
		printf("%d\n",v[k]);
		success=1; //정답이 있음을 표시.
    }
    else if(r>0)
    {
        for(k=1;k<=size;k++) //인덱스를 1부터 시작 편의를 위해 크기를 하나씩 늘림.
        { 
            if(map[i][k]==1 && visited[i]==0) //연결이 돼있고, 방문이 돼있지 않으면
            {
				v[r]=i;	//정답 값으로 저장
				visited[i] = 1; //방문한 것으로 설정
                map[i][k]=0;    map[k][i]=0; //이미 방문하여 방문하지 못하도록 0으로 설정
                r--; //정답을 저장하였으므로 인덱스 감소
                visit(k,r); //재귀호출
				visited[i] = 0; //dfs를 위해 원래값으로 초기화
				map[i][k]=1;    map[k][i]=1;
				r++;
            }
        }
    }
} 

void map_init()
{
	int i,j;
	for(i=0;i<11;i++) //1부터 시작해도 된다. 1부터 사용할 것이기에
	{
		for(j=0;j<11;j++) //1부터 시작해도 된다.
			map[i][j] = 0;
	}
}


int main() 
{ 
	int n,a,b;
	int r; //r을 쓰지 않고 size를 바로 넣어줘도 된다.
	while(scanf("%d %d %d",&size,&n,&start)!=EOF)
	{
		getchar();
		map_init(); //맵을 0으로 초기화
		while(n>0)
		{
			scanf("%d %d",&a,&b);
			getchar();
			add(a,b);
			n--;
		}
		success=0; r=size;
		for (n=0;n<11;n++) //방문 초기화
			visited[n] = 0;
    	visit(start,r);
    	if(success==0) //정답이 없으면 0 출력
        	printf("0\n");
	}
} 

```
