#include <stdio.h>

typedef struct team{
	char name[22]; //팀명
	int plus; //득점
	int minor; //실점
	int win; //이긴수
	int lose; //진수
	int plus_minor; //득실점(득점-실점)
	int winner[10]; //해당 팀과 경기에서 이겼는지의 여부를 1과 0으로 표기
}team;

void cal_score(team *list, char *buf, int count)
{
	int i,score_index=0,k,s;
	int key;
	int lose_index;
	int win_index;
	
	while(!(buf[score_index]==':' && buf[score_index-1] >= '0' && buf[score_index-1] <= '9' && buf[score_index+1] >= '0' && buf[score_index+1] <= '9'))
		score_index++; //팀명을 건너뛴다.
	for(i=0;i<count;i++)
	{
		k = 0;
		key = 0;
		while(list[i].name[k]) //동일한 팀명을 가진 팀명을 찾는다.
		{
			if(list[i].name[k] == buf[k])
			{
				k++;
				continue;
			}
			else
			{
				key = 1; //동일한 팀명이 아니면 key = 1;
				break;
			}
		}
		if (key == 0) //동일한 팀명을 찾았을 경우
		{
			list[i].plus+=(buf[score_index-1] -'0'); //왼쪽에서 해당 팀명을 찾았으므로, 득점은 왼쪽, 실점은 오른쪽이다.
			list[i].minor+=(buf[score_index+1] -'0');
			if(buf[score_index-1] > buf[score_index+1]) //스코어가 더 큰 경우
			{
				list[i].win++; //승리횟수를 늘려준다.
				win_index = i; //해당팀의 인덱스도 따로 저장한다.
			}
			else //진 경우
			{
				list[i].lose++; //진횟수를 늘려주고
				lose_index = i; //해당팀의 인덱스를 저장한다.
			}
			break;
		}
	}
	for(i=0;i<count;i++)
	{
		s = score_index+3; //:로부터 3만큼 더하면 팀명이 나온다.
		k = 0;
		key = 0;
		while(list[i].name[k]) //위에서와 마찬가지로 팀명이 같은 경우를 찾아본다.
		{
			if(list[i].name[k] == buf[s])
			{
				s++;
				k++;
				continue;
			}
			else
			{
				key = 1;
				break;
			}
		}
		if (key == 0) //팀명이 같을 경우
		{
			list[i].plus+=(buf[score_index+1] -'0'); //오른쪽의 스코어가 득점, 왼쪽의 스코어가 실점이다.
			list[i].minor+=(buf[score_index-1] -'0');
			if(buf[score_index+1] > buf[score_index-1]) //이긴팀, 진팀을 구분해서 인덱스와 횟수를 늘려준다.
			{
				list[i].win++;
				win_index = i;
			}
			else
			{
				list[i].lose++;
				lose_index = i;
			}
			break;
		}
	}
	list[win_index].winner[lose_index] = 1; //이긴팀의 winner에서 진팀의 인덱스를 1로 설정한다.
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort(team *list, int *index, int count) //1. 승리 수, 2. 승리 수가 같은 경우, 세트 득실점, 3. 그것도 같다면 해당 팀과의 승부에서 이긴 팀을 우선 순위로 둔다.
{
	int i,j,max;
	for(i=0;i<count;i++)
	{
		max = i;
		for(j=i+1;j<count;j++)
		{
			if((list[index[j]].win > list[index[max]].win) || //승리횟수 비교
			((list[index[j]].win == list[index[max]].win) && (list[index[j]].plus_minor > list[index[max]].plus_minor)) || //승리횟수가 같고, 세트 득실점을 비교
			((list[index[j]].win == list[index[max]].win) && (list[index[j]].plus_minor == list[index[max]].plus_minor) && (list[index[j]].winner[index[max]] == 1)))
				max = j;//마지막으로 이긴 횟수와, 세트 득심점이 같은 경우에는 winner 인덱스가 1인 팀을 우선 순위로 둔다.
		}
		swap(&index[i], &index[max]);
	}
}

void init_list(team *list, int count)
{
	int i,j;
	for(i=0;i<count;i++) //널값이 들어가는 것을 방지하기 위해 0으로 초기화 시켜준다.
	{
		list[i].win = 0;
		list[i].lose = 0;
		list[i].plus = 0;
		list[i].minor = 0;
		for(j=0;j<10;j++)
			list[i].winner[j] = 0;
	}
}

int main()
{
	team list[10];
	char buf[1024];
	int index[10];
	int count, i, k, match;

	while(scanf("%d",&count)!=EOF)
	{
		getchar();
		for(i=0;i<count;i++) //count는 팀의 수
		{
			fgets(list[i].name,22,stdin); //팀명을 읽어 들인다.
			k = 0;
			while(list[i].name[k] != '\n')
				k++;
			list[i].name[k] = '\0'; // '\n' 대신에 '\0'으로 바꾼다. fgets의 개행문자를 없애기 위해.
		}
		init_list(list,count); //0으로 초기화
		match = (count)*(count-1)/2; //경기의 횟수 = 팀의 수 * 팀의 수 -1 / 2
		for(i=0;i<match;i++) //경기 수만큼 읽어와서 스코어를 업데이트 시켜준다.
		{
			fgets(buf,1024,stdin);
			cal_score(list, buf, count);
		}
		for(i=0;i<count;i++) //인덱스를 팀 개수 만큼 초기화 & 각 세트득실점 계산
		{
			index[i] = i;
			list[i].plus_minor = list[i].plus - list[i].minor;
		}
		sort(list,index,count); //문제에서 요구하는 순서대로 팀 정렬
		for(i=0;i<count;i++) //문제에서 요구하는 요소들을 출력해준다.
		{
			k = index[i];
			printf("%d) %s %d %d %d-%d %d\n",i+1, list[k].name, list[k].win, list[k].lose, list[k].plus, list[k].minor, list[k].plus_minor);
		}
	}
}