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
