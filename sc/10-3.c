#include <stdio.h>

int n; //맵의 크기(nxn)
int map[10][10]; //맵
int key; //영역을 경계짓는 변수

const int EXIST = -1; //채울 수 있는 공간, 다이야가 있는 공간
const int NONE = 0; // 채우지 못하는 공간, 다이야가 없는 공간

void print_map()
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
}

int exist(void)
{
	int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(map[i][j] == EXIST) //채울 공간이 하나라도 있으면 return 1
				return 1;
	}
	return 0; //채울 공간이 하나도 없으면 return 0
}

int find(int i, int j, int value) //영역을 나눠서 값을 채워주는 함수
{
	if(i<0 || j<0 || i>=n || j>=n) { //인덱스를 넘는 예외처리, value를 다 채울 경우 맵을 순회하다가 인덱스를 넘겨 find가 종료된다.
    	return 0;
    }
	else if(exist() == 0){ //더이상 채울 곳이 없으면 출력
		print_map();
        return 1; //모든 공간을 다 채우면 return 1을 하여 더이상의 재귀호출을 막는다.
    }
	else if (map[i][j] < value && map[i][j] >= 0 && key != 1) //value보다 작으면서, exist가 아니라면
	{
		key = 0;
		while(i<n)
		{
			while(j<n)
			{
				if(map[i][j] < value && map[i][j] >= 0) //exist가 나올 때까지 index 증가.
					j++;
				if(map[i][j] == EXIST) //exist를 찾으면 해당 영역을 value로 채우면 된다.
				{
					key = 1;
					break;
				}
			}
			if (key == 1)
				break;
			i++;
			j=0;
		}
	} //위에서 i,j값을 찾아주고 그 주변에서 값을 채워주는 형태, key값이 1이기 때문에 위의 else if문은 더이상 수행되지 않는다.
	if(map[i][j] == EXIST){ //채울 수 있는 공간이면
		key = 1;
		map[i][j] = value; //값을 채우고, find 재귀를 수행한다.(방향 순서는 상관없음)
        if(find(i, j+1,value) || find(i+1, j,value)
		|| find(i, j-1, value) || find(i-1,j,value)) {
			return 1;
    	}
    }
	return 0;
}

int main()
{
	int i,j,k;
	char buf[1024];
	while(scanf("%d",&n)!=EOF)
	{
		getchar();
		for(i=0;i<n;i++)
		{
			k = 0;
			fgets(buf,1024,stdin);
			for(j=0;j<n;j++)
			{
				map[i][j] = buf[k]-'0';
				if (map[i][j] == 1)
					map[i][j] = -1; //1일 경우 exist로 설정
				k+=2;
			}
		}
		i = 1;
		while (exist()!=0) //더이상 채울 공간이 없을 때까지 value를 증가시키며 영역을 채움.
		{
   			key = 0;
			find(0,0,i);
			i++;
		}
	}
}
