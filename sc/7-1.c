#include <stdio.h>
//구한 subset을 출력해주는 함수
void print_subset(int *set, int n) {

        int i;
        printf("{ ");
        for (i = 0;i < n-1;++i)
               printf("%d ", set[i]);
        printf("%d }\n", set[n-1]);
}

void powerset(int *set, int n, int k, int m, int r) {
        if (n - k < m - r) return; //2번 재귀 호출하는데 2번째 호출 때 n,m,r은 고정 k값만 증가하여 원소k가 len을 넘어가는 것을 방지하고, 재귀를 종료시켜주는 부분
        if (r == m) { //출력조건 : 부분집합의 원소 개수가 충족할 때
               print_subset(set, m);
               return;
        }
        set[r] = k+1;
        powerset(set, n, k+1, m, r+1); //r+1을 하여 r==m을 만족하는 부분집합을 출력해준 후,
        powerset(set, n, k+1, m, r); //r==m을 만족하기 바로 직전에서 끝에 원소를 하나 증가시킨 원소를 출력해주기 위해 재귀해준다.
                                   //dfs라고 볼 수 있다. 1 2 -> 1 3 이런식으로 출력하다가 더이상 없으면 앞에 수를 키운다. (2 3)
}

int main() {

	int i;
	char buf[1024];
	int set[1024] = {0,};
	int len;
	while (fgets(buf,1024,stdin)!=NULL)
	{
		i = 0;
		len = 0;
		while(buf[i]!='\n'&&buf[i])
		{
			if (buf[i]>='0' && buf[i] <= '9')
				len++; //원소의 개수 측정
			i++;
		}

        printf("{ }\n");
        for (i = 1;i<len+1;++i) //i값은 부분집합 원소의 개수를 의미한다.
               powerset(set, len, 0, i, 0); //총 원소의 개수만큼 함수를 돌려준다.
	}
    return 0;
}
