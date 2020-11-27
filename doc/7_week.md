# 7주차-조합론

## 문제 1

### 문제설명

0~9까지의 숫자만을 원소로 갖는 집합이 주어졌을 때, 그 집합의 모든 부분집합을 출력하라.<br>
단, 부분집합에는 공집합과 자기자신까지 포함하며, 공집합일 경우에는 { }를 출력한다.<br>
모든 부분 집합을 출력할 때에는 원소의 개수가 작은 것부터 출력하고, 원소의 개수가 같은 부분집합일 경우 숫자가 작은 부분집합부터 출력한다.<br>
입력에는 집합의 원소들이 한 줄로 입력되는데, 각 원소 사이에는 공백이 있다. <br>
출력에는 모든 부분집합을 위에서 언급한 순서대로 출력하는데 원소와 원소 사이에는 콤마 대신 공백이 있어야 한다.<br>
<br>
### 실행 화면 예시

<img src="/img/7-1.png" width="60%" height="60%">

### 코드
```c
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

```

## 문제 2

### 문제설명

입력은 영어소문자만으로 구성된 최대 10글자의 문자열이다 (중복 가능).<br>
문자열의 모든 순열을 abc순으로 출력하라. 단, 같은 것을 중복해서 출력하지는 않는다.<br>
<br>
### 실행 화면 예시

<img src="/img/7-2.png" width="60%" height="60%">

### 코드
```c
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
```

## 문제 3

### 문제설명

교과서 참고: 41번<br>
<br>
제켄도르프의 정리에 따르면, 모든 정수는 서로 다른 피보나치 수들의 합으로 표현될 수 있다. 예를 들어,<br>
<br>
8 = 8<br>
20 = 13 + 5 + 2<br>
100 = 89 + 8 + 3<br>
<br>
연속된 피보나치 수를 사용하면 100 = 89 + 8 + 2 + 1 혹은 100 = 55 + 34 + 8 + 3 등으로도 표현할 수 있지만 (2와 1이 연속이고 55와 34가 연속이다),<br>
연속된 피보나치 수를 쓰면 안된다는 규칙을 추가하면, 한 가지 방법으로만 합을 구할 수 있다. 이 합은 다음과 같은 방식으로 계산할 수 있다.<br>
100보다 같거나 작은 피보나치 수 중에 제일 큰 것이 89다.<br>
100에서 89를 빼면 11이 되는데, 11보다 같거나 작은 피보나치 수 중에 제일 큰 것은 8이다.<br>
11에서 8을 빼면 3이 되고, 3은 피보나치 수이므로 100 = 89 + 8 + 3이다.<br>
<br>
입력 첫째 줄에는 문제의 개수 n (n <= 4,000)이 있고, 그 후 n줄에 걸쳐 100보다 작거나 같은 숫자가 있다. <br>
각 숫자에 대해, 어떤 피보나치 숫자들을 더해야 그 숫자가 나오는지 알아낸 후, 각 숫자들을 제곱하고 합한 값을 출력하라.<br>
<br>
### 실행 화면 예시

<img src="/img/7-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int main()
{	
	int fib[10] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}; //fib(10)까지의 원소 저장
	int testCase;
	int value;
	int result[10];
	int i,j;
	int answer;

	while(scanf("%d",&testCase)!=EOF)
	{
		getchar();
		while((testCase--)>0)
		{
			scanf("%d",&value);
			getchar();
			j = 0;
			for(i=9;i>=0;i--) //큰 수부터 찾기 위해 역순으로 for문을 돌렸다.
			{
				if (value >= fib[i]) //큰 수부터 value와 같거나 작은 수를 찾아서
				{
					value = value - fib[i]; //빼주고
					result[j++] = fib[i]; //저장해준다.
				}
				if (value == 0) //종료 조건
					break;
			}
			answer = 0;
			for(i=0;i<j;i++)
				answer = answer + (result[i] * result[i]); //각 숫자들을 제곱한 수를 더한 값을 저장해준다.
			printf("%d\n",answer);
		}
	}
}
```
