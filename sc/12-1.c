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
