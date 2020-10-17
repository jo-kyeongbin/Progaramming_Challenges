/*FIFO 형태의 자료형을 가진다. 먼저 들어온사람이 먼저 식사를 마친다.*/
#include <stdio.h>

int main(){
	int tables, i, k, min_index, key; //tables=테이블수, min_index=제일 먼저들어온 손님 저장, key=min_index의 초기값을 제어해주기 위한 변수.
	char buf[1024];

	scanf("%d",&tables);
	getchar(); //개행 문자를 없애주기 위한 표현
	char exist[tables];
	for(i=0;i<tables;i++) //비어있는 테이블로 초기화
		exist[i] = '#';
	scanf("%[^\n]s",buf); //개행문자를 무시하기 위한 표현
	i = 0;
	min_index = 0;
	while (buf[i])
	{
		if ('A'<=buf[i] && 'Z'>=buf[i])
		{
			for (k = 0;k < tables;k++)
			{
				if (exist[k] == '#') //비어있는 테이블이면 자리를 해당 문자로 채운다.
				{
					exist[k] = buf[i];
					break; //비어있는 테이블을 발견하여 자리를 찾았으므로, 반복문 종료.
				}
			}
			i++;
			continue;
		}
		if (buf[i] == '*') //식사를 마쳤다면
		{
			key = 0;
			for (k=0; k<tables; k++)
			{
				if (exist[k] != '#' && key == 0) //min_index의 초기값을 지정해주기 위해 key를 이용했다.
				{	
					min_index = k;
					key = 1;
				}
				if (exist[k] != '#' && exist[min_index] > exist[k]) //먼저 들어온 손님의 문자가 더 작으므로 (ex)A가 B보다 일찍 들어왔다.)
				{
					min_index = k;
				}
			}
			exist[min_index] = '#'; //일찍 들어온 손님이 식사를 마쳐서 비워줬다.
			i++;
			continue;
		}
		i++; //공백을 건너뛰기 위한 i++
	}
	for (k=0;k<tables;k++) //결과값 출력
	{
		if (k != tables - 1)
			printf("%c ",exist[k]);
		else
			printf("%c\n",exist[k]);
			
	}
}
