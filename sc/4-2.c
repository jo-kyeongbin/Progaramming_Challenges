#include <stdio.h>

int vaildation(char *text, char *s)
{
	int i;
	int key;
	while (*s != '\n')
	{
		key = 0;
		for(i=0;i<6;i++)
		{
			if (*s == text[i] || *s == ' ') //6개의 문자에 포함되는 문자인지 파악한다.
			{
				key = 1;
				break;
			}
		}
		if (key == 0) //해당하는 문자가 아닐경우 반복문 종료.
			break;
		s++;
	}
	if (*s == '\n') //모든 입력문을 순회하였고, 모두 6개의 문자에 포함되면 return 1
		return (1);
	else
		return (-1);
}

int convert_index(char a, char *text)
{
	int i;
	for (i=0;i<6;i++)
	{
		if (text[i] == a) //해당 문자를 인덱스로 변환하여 mapping 시켜준다.
			return i;
	}
	return 0; //validation을 거쳐왔기 때문에 매핑이 안될 이유는 없지만 안되면 인덱스 0에 해당하는 매핑을 하기 때문에 오류를 일으킨다.
}

void upper(char *s) //소문자를 대문자로 변경시켜준다. 문제에서 대소문자를 구분하지 않으므로 하나의 문자로 통일.
{
	int i = 0;
	while(s[i] != '\n')
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
}

int main()
{
	char text[8]; //행과 열의 카테고리 인덱스 총 6자리.
	char map_buf[38]; //순서대로 들어온 36개의 문자
	char map[6][6]; //6x6의 맵
	char buf[102]; //암호문을 받는 버퍼
	char result[100]; //평문을 받는 버퍼
	int i,j,k,p;

	while (fgets(text,8,stdin)!=NULL)
	{
		upper(text);
		fgets(map_buf, 38, stdin);
		k = 0;
		for(i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				map[i][j] = map_buf[k++]; //맵에 입력받은 36개의 문자를 저장해준다.
			}
		}
		while(fgets(buf,102,stdin)!=NULL)
		{
			upper(buf); //모든 암호문을 대문자로 변경
			if((vaildation(text,buf) == -1)) //없는 문자를 암호문에 포함시키면 에러 출력.
			{
				printf("-ERROR-\n");
				continue;
			}
			i = 0;
			p = 0;
			while(buf[i] != '\n')
			{
				if (buf[i] == ' ') //공백은 공백으로 유지
				{
					result[p++] = ' ';
					i++;
					continue;
				}
				if ((buf[i] >= 'A' && buf[i] <= 'Z')) //암호문자는 행과 열, 2문자씩 읽어온다.
				{
					if((buf[i+1] >= 'A' && buf[i+1] <= 'Z'))
					{
						j = convert_index(buf[i++], text); //인덱스로 변환
						k = convert_index(buf[i++], text);
						result[p++] = map[j][k]; //맵에서 찾아와서 result에 저장한다.
					}
					else //페어형태로 들어와야하는데 한개의 문자만 읽히면 맵핑을 못하므로, 에러 출력.
					{
						printf("-ERROR-\n");
						k = -3;
						break;
					}
				}
			}
			if (k != -3) //에러를 출력하지 않았다면 결과 출력.
			{
				result[p] = '\0'; //문자열을 출력해주기 위해 마지막에 널문자 추가.
				printf("%s\n",result);
			}
		}
	}
}