#include <stdio.h>
#define ABS(x) (((x)<0)?-(x):(x)) //절대값 메크로 함수

typedef struct position{
	int x; //x좌표
	int y; //y좌표
	int diff; //비토의 이사집과의 거리차이
}position;

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_x(int *index, position *list, int count) //인덱스 배열을 x좌표에 대해서 정렬
{
	int i,j,min;

	for (i=0;i<count;i++) //선택정렬
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].x < list[index[min]].x) min = j;
		swap(&index[i], &index[min]);
	}
}

void sort_y(int *index, position *list, int count) //인덱스 배열을 y좌표에 대해서 정렬
{
	int i,j,min;

	for (i=0;i<count;i++) //선택정렬
	{
		min = i;
		for(j=i+1;j<count;j++)
			if(list[index[j]].y < list[index[min]].y) min = j;
		swap(&index[i], &index[min]);
	}
}

int main()
{
	int count, result, i, k;
	int gap[1000]; //비토의 집과의 거리차 저장 변수
	int mid, min, x, y; //mid(중앙값):비토가 이사갈 좌표, min : 출력을 위해 최소 거리차를 가진 좌표 인덱스를 저장
	int sum; //거리차들의 총합을 저장
	char buf[1024];
	position list[1000];
	int index[1000]; //원래의 정보를 유지하기 위해 인덱스 배열 활용.

	while(scanf("%d %d",&count, &result)!=EOF)
	{
		getchar();
		sum = 0;
		mid = (count-1) / 2;
		for(i=0;i<count;i++)
		{
			fgets(buf,1024,stdin);
			list[i].x = buf[0]-'0'; //x좌표, y좌표를 받아온다.
			list[i].y = buf[2]-'0';
		}
		for(i=0;i<count;i++)
			index[i] = i; //처음의 순서로 인덱스 배열 초기화
		sort_x(index, list, count); //x좌표에 대해서 정렬
		x = list[index[mid]].x; //x좌표의 중앙값이 비토가 이사갈 집의 x좌표
		for(i=0;i<count;i++)
			index[i] = i;//처음의 순서로 인덱스 배열 초기화
		sort_y(index,list,count);//y좌표에 대해서 정렬
		y = list[index[mid]].y; //y좌표의 중앙값이 비토가 이사갈 집의 y좌표
		for(i=0;i<count;i++)
		{
			list[i].diff = ABS(list[i].x - x) + ABS(list[i].y - y); //구한 비토의 좌표로부터 친척집들과의 차이를 계산하여 저장.
			sum += list[i].diff; // 차이값을 합산
			gap[k++] = list[i].diff; //차이값들을 따로 배열로 저장한다. (들어온 순서 고려)
		}
		printf("%d\n",sum); //거리차의 총합을 출력해준다.
		for(i=0;i<count;i++)
			index[i] = i;//y좌표에 대해 정렬되어 있는 인덱스를 다시 초기화 시킨다.
		for(i=0;i<result;i++)
		{
			min = 0;
			for(k=0;k<count;k++)
				if(gap[k] < gap[min]) min = k;
			printf("%d %d\n",list[min].x, list[min].y); //가장 가까운 거리 순으로 출력해준다.
			gap[min] = 9999; //이미 출력한 것은 제외하기 위해 9999로 초기화.
		}
	}
}