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
