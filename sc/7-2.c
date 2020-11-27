#include <stdio.h>
//중복하는 원소를 포함하는 순열

int chk[10]; //방문여부를 체크하는 변수
char word[10]; //결과값을 저장해주는 변수

void dfs(int depth, int len, char *input){
	int i;
	int before;
    if (depth == len){ //원소를 출력하며 재귀를 종료하는 부분
        for (int i=0; i<len; ++i) printf("%c", word[i]);
        printf("\n");
        return;
    }
    before = -1;
    for (i=0; i<len; ++i){
        if (!chk[i] && (i == 0 || before != input[i])) {
            before = input[i]; //초기에는 상관이 없는데 재귀가 끝나고 chk[i] = 0 이 수행되고 다시 반복문이 진행될 때,
            word[depth] = input[i];	//중복된 원소가 나오면 before != input[i] 조건문에 의해 중복출력을 제외시켜준다.
            chk[i] = 1; //방문했는지 여부를 표시해준다. 기본적인 순열을 충족시켜주기 위한 변수.
            dfs(depth + 1,len,input); //depth를 1증가하여 재귀호출 해준다.
            chk[i] = 0; //깊이 우선 탐색을 위해 출력 바로 직전에서 원소를 바꿔본다.
        }
    }
}
 

void sort_input(char *input, int len) //원소를 정렬해주는 함수, 선택정렬을 활용하였다.
{
	char temp;
	int i,j;
	int min;
	for(i=0;i<len;i++)
	{
		min = i;
		for(j=i+1;j<len;j++)
			if (input[j]<input[min]) min = j;
		temp = input[min];
		input[min] = input[i];
		input[i] = temp;
	}
}

int main() {
    char buf[1024];
	char input[10];
	int i = 0;
	int len = 0;
	while(fgets(buf,1024,stdin)!=NULL)
	{
		while(buf[i]!='\n'&&buf[i])
		{
			if (buf[i]>='a' && buf[i]<='z')
			{
				len++;
				input[len-1] = buf[i];
			}
			i++;
		}
		sort_input(input, len); //정렬을 한 후
		dfs(0,len,input); //함수를 호출해준다.
	}
    return 0;
}