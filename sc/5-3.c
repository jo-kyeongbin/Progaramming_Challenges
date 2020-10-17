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