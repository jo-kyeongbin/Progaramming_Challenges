#include <stdio.h>
#include <stdbool.h>
#define INF -12345

bool visited[20] = {};
int dist[20] = {};

int get_max_vertex(int n) {
	int v;
	// 아직까지 방문하지 않은 node를 앞 순서부터 찾아낸다.
	for (int i = 0; i < n; i++) {
		if (visited[i] == false) {
			v = i;
			break;
		}
	}

	// 앞에서 찾아낸 v 인덱스의 node보다 dist[]가 짧은 게 있다면?
	// 위 아래 for문을 합치면, 섬처럼 갇혀 있는 node에 대한 탐색이 불가능하다.
	// 1-2-3과 4로 이루어진 그래프는 4의 dist[]가 항상 INF이므로.

	for (int i = 0; i < n; i++) {
		if (visited[i] == false && (dist[i] > dist[v])) {
			v = i;
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

		if (dist[u] == INF) return (-1); // 만약 그렇게 찾아낸 node의 dist 값이 INF면 종료 (섬이기 때문)

	//	cout << u+1 << ' '; // 종료되지 않았다면 연결된 node이므로 출력.
		result += dist[u];
		// 방문이 끝난 다음에는 dist 값을 새로 방문한 node 기준으로 다시 초기화해줘야 한다.
		for (int v = 0; v < n; v++) {
			if (map[u][v] != INF) { // 전체를 탐색하며 u로부터 v로 가는 길이 연결되어 있다면,
				if (visited[v] == false && map[u][v] > dist[v]) { // 아직 방문하지 않았고, 원래의 dist 보다 짧다면
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
		printf("%d\n",prim(map,0,v));
	}
}