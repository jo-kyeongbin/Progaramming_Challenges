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