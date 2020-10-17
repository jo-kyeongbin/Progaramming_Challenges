#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 10000

typedef struct dic{ //bigram을 저장하는 자료구조
	char key[3]; //bigram을 저장하는 캐릭터 배열, 널 문자를 포함하여 크기가 3이다.
	int frq; //빈도를 표현해주는 변수
	int visit; // 최소값을 출력해줄 때 출력했는지의 여부를 표현하는 변수
} Dictionary;

void add_value(char a, char b, Dictionary *p)	//처음 등장하는 bigram을 초기화시켜주는 함수
{
	p->key[0] = a;
	p->key[1] = b;
	p->key[2] = '\0';
	p->frq = 1; //빈도의 초기값 = 1 처음 등장했으므로,
	p->visit = 0;
}

void print_value(Dictionary *p[], int i, int max_count, int max_frq) //i = Dictionary의 총 개수, max_count = 최대 빈도를 가진 bigram의 개수, max_frq = 해당되는 빈도 수
{
	int l;
	int total = i; //중복되지 않는 bigram의 개수(Ditionary p의 총 개수)
	int min_index = -1; //bigram이 없을 경우 -1이 유지된다.
	char min[3]; //제일 작은 아스키코드의 bigram을 저장하기 위한 변수
	min[2] = '\0';
	if (max_count == 0)
	{
		printf("Not present\n");
		return;
	}
	while (max_count)
	{
		l = 0;
		min[0] = 'z'+1; //어떤 값이 와도 min으로 대체되기 위해 초기값으로 무조건 큰 값으로 초기화
		min[1] = 'z'+1;
		while (l < total)
		{
			if (p[l]->visit == 0 && p[l]->frq == max_frq)
			{
				if(p[l]->key[0] < min[0] || (p[l]->key[0] == min[0] && p[l]->key[1] < min[1]))
				{
					min[0] = p[l]->key[0];
					min[1] = p[l]->key[1];
					min_index = l;
				}
			}
			l++;
		}
		max_count--;
		if (min_index != -1 && min[0] != 'z'+1) //min값이 존재하면
		{
			if (max_count != 0) //마지막 출력은 개행을 포함하여야 하므로 if문으로 구분
				printf("%s ", min);
			else
				printf("%s\n",min);
			p[min_index]->visit = 1; //출력이 되었으면 visit을 1로 초기화하여 비교대상에서 제외시킨다.
		}
	}
	if (min_index == -1) //bigram이 없을 경우
			printf("Not present\n");
}
int main()
{
	Dictionary *p[BUFSIZE];
	char *n;
	int i;
	int j;
	int k = 0; //중복되지 않는 bigram의 개수
	int max_count = 0; //최대 빈도 수를 가진 bigram의 개수
	int key = 0; //처음 등장한 bigram에 대해 제어해주는 변수
	int max_frq = 0; //제일 큰 p[i]->frq의 값이 저장된다. 즉 가장 큰 빈도 수.

	n = (char *)malloc(BUFSIZE); //고정배열로 선언해도 무방하다.
	while (fgets(n, BUFSIZE, stdin)!=NULL)
	{
		for (i = 0; i < sizeof(p) / sizeof(Dictionary *); i++)
    	{
        	p[i] = malloc(sizeof(Dictionary));
    	}
		i = 0;
		while (n[i] != '\n' && n[i])
		{
			if (('a' <= n[i] && 'z' >= n[i]) || (n[i] >= 'A' && n[i] <= 'Z')) //만약에 영문자가 연속된다면, bigram이라면
			{	
				if (('a' <= n[i + 1] && 'z' >= n[i + 1]) || (n[i + 1] >= 'A' && n[i + 1] <= 'Z'))
				{
					j = i; 
					while (j) //현재까지 읽어온 버퍼를 순회하면서, 이전에 나온 bigram이 사전에 있으면 빈도 수(frq)를 증가시켜준다.
					{
						if (n[i] == p[j]->key[0])
						{
							if (n[i+1] == p[j]->key[1])
							{
								p[j]->frq++; //Dictionary에 존재하는 bigram일경우 frq(빈도)를 증가시켜준다.
								key = 1;
							}
						}
						j--;
					}
					if (key == 0) //이전에 등장하지 않은 새로운 bigram일 경우.
						add_value(n[i], n[i + 1], p[k++]);
				}
			}
			i++;
			key = 0;
		}
		for(i=0;i<k;i++)
		{
			if(p[i]->frq < 2) //문제에서 2회 이상 등장하는 bigram을 논하였으므로,
				p[i]->visit = 1; //visit을 1로 만들어 제외시켜준다.
			if(p[i]->frq >= 2)
			{
				if (p[i]->frq >= max_frq)
				{
					if (max_frq < p[i]->frq) //큰 빈도 수가 존재하면
						max_count = 0;	//큰 빈도 수를 가진 bigram의 개수.
					max_frq = p[i]->frq; //큰 빈도 수가 존재하지 않으면 같은 값으로 초기화되고, 큰 빈도 수가 존재하면 새로운 값으로 변한다.
					max_count++; //해당 빈도 수의 개수 카운팅.
				}
			}
		}
		print_value(p,k,max_count,max_frq); //p = Dictionary, k = Dictionary의 총 크기, max_count = 최대 빈도의 bigram의 개수, max_frq = 최대 빈도수)
		k = 0;	//다음으로 오는 테스트 케이스들을 처리하기 위해 변수들을 초기화
		max_count = 0;
		max_frq = 0;
		for (i = 0; i < sizeof(p) / sizeof(Dictionary *); i++)
   		{
       		free(p[i]);
    	}
		free(n);
		n =(char *)malloc(BUFSIZE);
	}
	free(n); //만약에 더이상 테스트케이스가 존재하지 않으면 free를 선언.
}