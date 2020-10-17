# 5주차

## 문제 1

### 문제설명

한 문자열이 UTF-8 형식으로 최대 100글자가 주어진다. 이 문자열에는 Unicode로 영문자와 한글이 포함되어 있다.<br>
한자나 특수문자(7 bit 아스키 코드에 포함되지 않는 2 Byte 특수문자)는 없다고 가정한다.<br>
이 문자열에 있는 모든 영문자를 앞에서 우선 출력하고, 모든 한글 문자를 영문 뒤에 출력하여라.<br>
그 다음 줄에 영문자의 개수, 한글 문자의 개수, 총 개수를 차례로 출력하라.<br>

------

입력<br>
한글과 영문이 혼용된 문자열<br>

출력<br>
영문 한글 순서로 정렬된 문자열<br>
영문자수 한글문자수 총문자수<br>

### 실행 화면 예시

<img src="/img/5-1.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>
/*
간단해보이지만 한글 유니코드의 특징을 잘 알아야 풀 수 있다.
한글은 영문자와 다르게 3바이트를 차지한다. (환경에 따라 2바이트 일 수 있음)
한글은 최상위 비트가 1로 시작한다. (0x80(1000 0000)과 and연산을 하였을 때 1이라는 결과가 나옴.)
*/
int main()
{
	int kor, eng;
	char buf[1024]={0};
	char korean[1024] = {0};
	char english[1024] = {0};
	int i, j, k;
	while (fgets(buf,1024,stdin)!=NULL)
	{
		kor = 0;
		eng = 0;
		i = 0;
		j = 0;
		k = 0;
		while (buf[i])
		{
			if(buf[i] & 0x80) //만약에 한글이면
			{
				korean[j++] = buf[i++];
				korean[j++] = buf[i++];
				korean[j++] = buf[i++]; //3바이트 저장
				kor++; //한글 글자 수 증가
			}
			else //영문자면
			{
				if (buf[i] != '\n')
				{
					english[k++] = buf[i++]; //1바이트 저장
					eng++; //영어 글자 수 증가
				}
				else
					i++; //fgets는 개행문자까지 버퍼에 저장하므로, 개행문자는 건너뛴다.
			}
		}
		english[k] = '\0'; //문자열이므로 마지막에 널문자를 추가해준다.
		korean[j] = '\0';
		printf("%s",english); //영어, 한글순으로 출력해주고,
		printf("%s",korean);
		printf("\n");
		printf("%d %d %d\n",eng,kor,eng+kor); //영어 수, 한글 수, 영어랑 한글의 총합 수를 출력해준다.
	}
}
```

## 문제 2

### 문제설명

두 친구가 끝말잇기를 한다. 끝말잇기가 성공한 부분까지 출력하여라.<br>
단, 한 단어는 두 번 나올 수 없다.<br>
<br>
각 입력 줄에는 단어의 수 n(1<=n<=10)이 먼저 나오고 이어서 n개의 단어가 주어진다.<br>
<br>
모든 단어는 알파벳 소문자로만 구성된다.<br>
<br>

### 실행 화면 예시

* 입력

	    8 dog green name element table element target title
	    5 power ready yellow ultra auto
	    2 test target
	    1 a
    
* 출력

	    dog green name element table 
	    power ready yellow 
	    test target 
	    a 

### 코드
```c
#include <stdio.h>

void remove_same_word(char *result, int *index) //단어의 중복을 배제한 결과값을 출력해주는 함수
{
	int i=0,j=0;
	int k,l;
	char answer[1024];
	while(index[i]!=-1)
	{
		j = i + 1; //i번째 단어와 i+1번째 단어를 비교한다.
		while(index[j]!=-1)
		{
			k = index[i];
			l = index[j];
			while (result[k]==result[l] && result[k] != ' ') //단어가 불일치할 때까지, 단어가 끝날 때까지 반복문 수행.
			{
				k++;
				l++;
			}
			if (result[k] == ' ' && result[l] == ' ' && (result[k-1] == result[l-1])) //만약에 단어가 일치한다면
			{
				for(i=0;i<index[j]-1;i++) //0부터 해당 단어전까지 값을 저장한다.
					answer[i] = result[i];
				answer[i++] = ' ';
				answer[i]= '\0';
				printf("%s\n",answer); //저장된 값을 출력한다.
				return;
			}
			j++;
		}
		i++;
	}
	printf("%s\n",result); //만약에 일치하는 단어가 없었다면 원래의 결과값 그대로 출력
}

int main()
{
	char buf[1024];
	char result[1024];
	int index[11];
	int i, j, k, key;
	while(fgets(buf,1024,stdin)!=NULL)
	{
		for(i=0;i<11;i++)
			index[i] = -1; //단어의 위치를 알려주는 인덱스 초기화
		i = 0;
		j = 0;
		k = 0;
		key = 1;
		while(buf[i]!='\n' && key == 1 && buf[i])
		{
			if(buf[i]>='0' && buf[i]<='9') //단어의 수는 건너뛰었다.
			{
				i++;
				continue;
			}
			if(buf[i]==' ')
			{
				if(!(buf[i-1]>='0' && buf[i-1]<='9')) //처음 공백이 등장한 것이 아니라면
					result[j++] = buf[i]; //결과값에 공백 추가
				i++;
				continue;
			}
			if(buf[i]>='a' && buf[i]<='z') //단어가 나오면
			{
				if(buf[i-1]==' ')
					index[k++] = j; //result에 저장된 단어의 첫부분을 가리키는 인덱스를 저장한다.
				result[j] = buf[i];
				if(buf[i+1]==' ')
				{
					if(buf[i+2] != buf[i]) //끝말잇기 이므로, 단어의 끝부분과 시작점이 일치해야 한다.
					key = 0; //일치하지 않으면 key가 0이 되어 반복문이 종료된다.
				}
				i++;
				j++;
			}
		}
		result[j++] = ' '; //마지막 단어 뒤에도 공백을 넣어서 remove_same_word 함수에서 편의성을 얻었다.
		result[j] = '\0';
		remove_same_word(result,index);
	}
}
```

## 문제 3

### 문제설명

각 알파벳을 특정 알파벳으로 치환해서 암호를 만들었다고 하자. 이 암호를 일부는 깼는데, 다 깨진 못했다.<br>
입력 첫째 줄에는 the quick brown fox jumps over the lazy dog의 암호화된 버젼이 주어지는데, 암호를 다 깨진 못해서 일부는 ?로 되어 있다.<br>
이 문자열은 알파벳 소문자, 물음표, 공백으로만 구성되며 암호화 과정에서 모순이 없음이 보장된다.<br>
입력 둘째 줄에는 총 단어의 개수 n이 주어지고(1 <= n <= 10),<br>
셋째 줄에는 암호화되지 않은 단어 n개가 주어진다.<br>
넷째 줄에는 그 단어들을 암호화된 단어 n개가 주어지는데, 순서는 섞여 있다.<br>
각 단어의 최대 길이는 10이며 알파벳 소문자로만 구성된다.<br>
<br>
이 단어들을 이용해 어떤 글자가 어떤 글자로 암호화되는지를 알아내, the quick brown fox jumps over the lazy dog의 암호화된 버젼을 출력하라.<br>
암호화된 문장을 복호화하기 위해서는 서로 다른 문자가 같은 문자로 암호화되는 경우가 발생하면 안된다는 사실을 명심하라.<br>
모든 테스트 케이스에 대하여 정답이 존재하며 정답은 유일하다.<br>

### 실행 화면 예시

<img src="/img/5-3.png" width="60%" height="60%">

### 코드
```c
#include <stdio.h>

int cyclehas(int n, int x)
{
    if (n == x) return 1;	//x가 해당 수열에 존재하면 1을 리턴해주는 함수이다.
    while (n != 1) {	//n이 1이 될때까지
        if (n % 2 == 0) n /= 2;	//짝수이면 2로 나누고,
        else n = 3*n + 1;	//홀수이면 3n+1을 수행한다.
        if (n == x) return 1;
    }
    return 0;	//해당 수열에 존재하지 않으면 0을 리턴한다.
}

int main(void)
{
    int n, x;

    while (scanf("%d %d", &n, &x) == 2) {
        if (cyclehas(n, x)) printf("Y\n");	//1을 리턴하여 참이면 Y
        else printf("N\n");	//아니면 N을 리턴한다.
    }
    return 0;
}

```
