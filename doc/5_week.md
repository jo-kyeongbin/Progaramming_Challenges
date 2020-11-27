# 5주차-문자열2

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

typedef struct word{
	int index; //단어의 시작 인덱스를 저장
	int number; //ex)aabbccaa = 11223311 로 저장, 규칙을 찾기 위한 형태로 변환
}word;

int my_atoi(char *s) //문자열을 정수형으로 바꿔주는 함수
{
	int result = 0;
	while(*s)
	{
		result = result * 10 + (*s - '0');
		s++;
	}
	return result;
}

void get_data(char *sequence, struct word *data) //단어의 시작점과 해당 단어를 숫자로 표현하여 저장 (aabbccaa면 11223311) 
{
	int i = 0;
	int k = 0;
	int j;
	int l;
	int index;
	char numbers[100];
	int map[256] = {0,}; //아스키코드로 매핑하기 위해 256으로 크기를 잡음(128도 상관없는데 넉넉히 잡음), 함수내에서만 사용된다.
	int value;
	while(sequence[i])
	{
		value = 1;
		index = i;
		while (!(sequence[index] >= 'a' && sequence[index] <= 'z')) //소문자가 아니면 넘긴다.
			index++;
		data[k].index = index; //단어가 나오면 처음위치를 저장한다.
		j = 0;
		while(sequence[i] != ' ' && sequence[i] != '\n' && sequence[i]) //소문자이면
		{
			if (map[sequence[i]]==0 && sequence[i] != '0') //맵에 저장되어 있지 않으면 새로운 value로 초기화
				map[sequence[i]] = value++; //해당 소문자를 value에 해당하는 숫자로 매핑
			numbers[j++] = map[sequence[i]] + '0'; //출력을 위해 변환된 값을 저장.
			i++;
		}
		for(l=0;l<256;l++)
			map[l]=0; //단어마다 매핑을 새롭게 해야하므로, 0으로 초기화
		numbers[j] = '\0';
		data[k++].number = my_atoi(numbers); //숫자로 변환된 단어를 저장한다.
		i++;
	}
}

void remove_it(char *text, char c) //문자열 text에 캐릭터 c가이 존재하면 문장에서 제거해주는 함수이다.
{
	int k = 0;
	while(text[k]!='\n' && text[k])
	{
		if (text[k] == c)
			text[k] = '0';
		k++;
	}
}

void init_mapping(char cipher_c, char plain_c, char *cipher, char *plain, char *map) //?를 포함한 문장에서 얻은 정보를 맵에 추가하는 함수. (한글자만 알아도 해당 단어의 모든 부분이 매핑 가능한 점을 이용)
{
	int c_index = 0;
	int p_index = 0;
	while(cipher[c_index]!='\n' && cipher[c_index])
	{
		if (cipher[c_index] == cipher_c)
		{
			while(cipher[c_index]!=' ' && c_index != 0) //단어가 공백 단위로 이루어지므로, 해당 단어의 시작점을 찾기 위해 index--를 수행한다.
				c_index--;
			if (c_index != 0) //문장의 첫부분이 아니면 공백이므로 i++을 해준다.
				c_index++;
			break; //해당 부분을 찾았으므로 반복문을 종료한다.
		}
		c_index++;
	}
	while(plain[p_index]!='\n' && plain[p_index]) //평문도 마찬가지로 해당 위치를 찾아준다.
	{
		if (plain[p_index] == plain_c)
		{
			while(plain[p_index]!=' ' && p_index != 0)
				p_index--;
			if (p_index != 0)
				p_index++;
			break;
		}
		p_index++;
	}
	while(plain[p_index]>='a' && plain[p_index] <= 'z') //찾은 위치를 이용하여 단어가 끝날때까지 맵에다가 저장해준다.
	{
		map[plain[p_index]] = cipher[c_index];
		plain[p_index] = '0'; //찾은 부분은 0으로 처리해준다. remove_it()함수 역할
		cipher[c_index] = '0';
		p_index++;
		c_index++;
	}
}

int validation(struct word *plain_data, char plain_c, char *plain) //plain 문자열에 plain_c(?를 포함한 문자열 입력 중 알파벳인 부분)이 있는지 여부를 찾아주는 함수
{
	int i=0,k=0;
	int count = 0;
	int exist[10] = {0,}; //단어의 수가 최대 10이므로 크기를 10으로 정함.
	while(plain[i]!='\n')
	{
		i = plain_data[k].index;
		while(plain[i] != ' ' && plain[i] != '\n')
		{
			if(plain[i] == plain_c)
			{
				exist[k] = 1; //해당 문자가 존재하면 1로 둔다.
				break;
			}
			i++;
		}
		k++;
	}
	while(k>=0)
	{
		if (exist[k] == 1) //존재하는 단어가 있을 때마다 count++
			count++;
		k--;
	}
	if (count == 0) //존재하는 단어가 없으면 리턴 0
		return 0;
	if (count > 1) //존재하는 단어가 2개이상이면 리턴 -1(존재하는 단어가 2개이상이면 매칭이 안되서 -1로 구분하였다.)
		return -1;
	return 1; //존재하는 단어가 1개일 때 리턴 1
}

int main()
{
	char map[256]; //map['a']~map['z']까지의 값을 채워야한다.
	char sen[44] = "the quick brown fox jumps over the lazy dog";
	char buf[1024]; //?를 포함한 sen을 암호화한 문자열 입력
	char plain[1024]; //평문화된 단어들의 입력
	char cipher[1024]; //암호화된 단어들의 입력
	word plain_data[10]; //단어의 최대 갯수가 10이므로 크기가 10이다. 평문화된 단어의 시작점과 패턴을 저장하는 구조체.
	word cipher_data[10]; //암호화된 단어의 시작점과 패턴을 저장하는 구조체
	int i,word,k,count,c_index,p_index,key=1;

	while (fgets(buf,1024,stdin)!=NULL)
	{
		scanf("%d",&word);
		getchar();
		fgets(plain,1024,stdin);
		fgets(cipher,1024,stdin);
		get_data(plain,plain_data); //plain_data를 다루어야하므로 먼저 수행.
		i = 0;
		while(buf[i]!='\n')
		{
			if(buf[i]=='?') //?인 부분은 넘긴다.
			{
				i++;
				continue;
			}
			else //단어 혹은 공백이라면
			{
				if(buf[i]!=' ') //공백이 아니라면
				{
					map[sen[i]] = buf[i]; //map[평문] = 암호문;
					if(validation(plain_data,sen[i],plain) == 1) //sen[i]에 해당하는 캐릭터값이 plain에 단 하나 존재한다면.
						init_mapping(buf[i], sen[i], cipher, plain, map); //해당 위치의 단어를 찾아서 맵에 저장해준다.
					if(validation(plain_data,sen[i],plain) != 0) //sen[i]가 존재한다면 평문과 암호문에서 sen[i]를 지운다. -1리턴을 해도 지워도 상관없는 이유는 163라인에서 이미 추가를 하였기 때문이다.
					{
						remove_it(plain,sen[i]);
						remove_it(cipher,buf[i]);
					}
				}
				i++;
			}
		}
		get_data(plain, plain_data); //remove_it을 수행하였기 때문에 값을 업데이트 시켜준다.
		get_data(cipher,cipher_data);
		while(key==1) //while문을 한번만 수행해도 거의 대부분 완성된다. 그러나 안정성을 위해 key를 두어 validation하였다.
		{
			for(i=0;i<word;i++) //plain_data의 인덱스는 고정해주고
			{
				count = 0;
				for(k=0;k<word;k++) //cipher_data의 인덱스를 변경하며 비교해준다.
				{
					if(plain_data[i].number == cipher_data[k].number && plain_data[i].number != 0) //평문과 암호문의 패턴이 동일한 것을 찾는다.
					{
						count++; //찾았으면 count를 증가한다.
						c_index = cipher_data[k].index; //그때의 인덱스를 저장해준다.
					}
				}
				if(count == 1) //같은 패턴이 오로지 하나만 존재하면
				{
					p_index = plain_data[i].index; //해당 plain의 인덱스를 저장하고
					while(plain[p_index] != ' ' && plain[p_index] != '\n') //단어가 끝날 때까지
					{
						map[plain[p_index]] = cipher[c_index]; //매핑과 동시에 remove_it을 수행하여 제거한다.
						remove_it(plain,plain[p_index]);
						remove_it(cipher,cipher[c_index]);
						p_index++;
						c_index++;
					}
				}
			}
			i = 0;
			while(plain[i]) //plain이 모두 0으로 바뀌어 map이 완성되었는지를 파악.
			{
				if(plain[i]>='a' && plain[i] <= 'z')
					break;
				i++;
			}
			if(plain[i] == '\0') //만약에 plain에 소문자가 없이 0만 존재하여 널문자를 가리킨다면
				key = 0; //key를 0으로 두어서 위의 반목문을 종료한다.
			else //그렇지 않으면 remove_it을 위에서 수행했을 것이므로 get_data를 수행해준다.
			{
				get_data(plain,plain_data);
				get_data(cipher,cipher_data);
			}
		} //key가 0이 되었다면 반복문 종료.
		for(i=0;i<44;i++) //이제 문제에서 요구하는 문장의 암호문을 출력해준다.
		{
			if(sen[i]>='a' && sen[i] <= 'z')
				printf("%c",map[sen[i]]);
			if(sen[i] == ' ')
				printf(" ");
		}
		printf("\n");
	}
}
```
