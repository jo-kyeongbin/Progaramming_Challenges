#include <stdio.h>
#include <stdlib.h>
/*어떤 상황에 No mushroom, empty, Wrong command인지 구별하는 것이 중요하다.*/
void reverse(int *size, int count) //버섯의 순서를 뒤집는 함수
{
	int i;
	int temp[count];
	for(i=0;i<count;i++)
		temp[i] = size[count -1 -i]; //버섯의 개수가 count이므로 count-1이 인덱스로 된다.
	for(i=0;i<count;i++)
		size[i] = temp[i];
}

int get_length(char *s) //문자열의 길이를 측정하는 함수
{
	int i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return i;
}

int my_atoi(char *buf) //문자열을 정수형으로 바꿔주는 함수
{
	int i;
	int length = get_length(buf);
	int result;
	result = buf[0] - '0'; // 초기값 설정, '0'(45)을 빼면 숫자값이 나온다.
	for(i=1;i<length - 1;i++) //i = 0부터 시작하려면 처음에 result = 0을 넣고 for문을 i = 0부터 시작하면 된다.
		result = (result * 10) + (buf[i] - '0');
	return result;
}

int main()
{
	char *buf; //버섯의 리스트를 받는 버퍼
	int temp;
	char *op;
	int *result;
	int size[1000];
	char count_buf[6];
	int count, i, k, index, key;
	while(fgets(count_buf,6,stdin)!=NULL){
	count = my_atoi(count_buf); //읽어온 문자열을 정수로 변환, count_buf는 버섯의 개수를 의미한다.
	if (!(count >= 0 && count <= 1000)) //버섯의 개수 제한 (0부터 1000까지만 가능)
	{
		printf("Wrong Command!\n");
		continue;
	}
	buf = (char *)malloc(sizeof(char)*2048);
	scanf("%[^\n]s",buf); //개행을 무시하여 버섯의 리스트를 받는다.
	i=0;
	temp = 0; //문자열로 들어온 버섯의 크기를 int로 변경해준 결과를 저장해주는 변수.
	k = 0;
	key = 0;
	while (buf[i] && key == 0) //잘못된 명령어를 입력하였을 때, key가 1이 되어 반복문 종료.
	{
		while (buf[i] != ' ' && buf[i]) //my_atoi를 사용하지 않은 이유는 공백을 기준으로 문자열만 숫자로 변경하면 되기 때문입니다.
		{//while문에 buf[i]가 있는 이유는 널문자를 넘기면 세그멘테이션 오류가 발생합니다.
			if (buf[i] >= '0' && buf[i] <= '9')
				temp = (temp * 10) + (buf[i] - '0');
			i++;
		}
		if (k < count) //버섯의 개수를 넘기지 않으면 버섯의 크기를 size에 저장해준다.
		{
			if (temp >= 1 && temp <= 1000000)
				size[k++] = temp;
			else //버섯의 크기의 범주를 넘는 버섯이 들어오면 Wrong Command!
			{
				printf("Wrong Command!\n");
				key = 1;
			}
		}
		temp = 0;
		if (buf[i]) //라인60의 while문이 종료되거나, 애초에 공백문자일 경우, 즉 공백문자를 건너뛰기 위해 i++수행
			i++;
	}
	op = (char *)malloc(sizeof(char)*100000);
	scanf("%s",op); //명령어 리스트를 받는다.
	getchar();
	i = 0;
	while (op[i] && key == 0) //key는 No mushrooms를 발생하였을 때 1이 된다.
	{
		switch(op[i])
		{
			case 'R':
				index = 0;
				while (index < count) //버섯의 개수만큼 반복문 수행
				{
					if(size[index] > 0) //버섯이 존재하면, 즉 0보다 큰 버섯이 존재하면 종료
						break;
					index++;
				}
				if (index == count && size[index] == 0) //버섯이 존재하여 중간에 종료됐으면, index가 count랑 다르고, size[index]가 0이 아니다.
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				reverse(size,count); //버섯이 존재하기 때문에 R명령수행.
				break;
			case 'S':
				index = 0;
				while (index < count) //마찬가지로 버섯이 존재하는지 여부를 파악.
				{
					if(size[index] > 0)
						break;
					index++;
				}
				if (index == count && size[index] == 0)
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				if (index + 1 < count)
				{
					for(k=index + 1;k<count;k++)
					{
						if(size[k]<size[index] && size[k] != 0) //버섯을 비교하여 0이 아닌 작은 값에 대해 최소값이 나오면 해당 인덱스를 저장한다.
							index = k;
					}
				}
				if (size[index] != 0)
					size[index] = 0; //S명령을 수행하여 제일 작은 버섯을 지운다.
				break;
			case 'B':
				index = 0;
				while (index < count) //마찬가지로 버섯의 존재여부를 파악한다.
				{
					if(size[index] > 0)
						break;
					index++;
				}
				if (index == count && size[index] == 0)
				{
					printf("No mushrooms!\n");
					key = 1;
					break;
				}
				if (index + 1 < count)
				{
					for(k=index + 1;k<count;k++)
					{
						if(size[k]>size[index] && size[k] != 0) //이번에는 제일 큰 버섯을 찾는다.
							index = k;
					}
				}
				if (size[index] != 0)
					size[index] = 0; //B명령을 수행하여 제일 큰 버섯을 지운다.
				break;
			default:
				printf("Wrong Command!\n"); //R 또는 B 또는 S가 아닌 경우 잘못된 명령어이다.
				key = 1;
		}
		i++;
	}
	k = 0;
	result = (int *)malloc(sizeof(int)*1024);
	for (i=0;i<count;i++) //결과를 출력해주기 위해 result 배열에 0이 아닌 값을 담는다.
	{
		if (size[i] > 0)
			result[k++] = size[i];
	}
	if (k == 0 && key == 0) //size가 0보다 큰 버섯이 없으면서, 즉 버섯이 존재하지 않으며, 위에서 오류를 발생하지 않았다면)
		printf("Empty!\n");
	if (key == 0 && result[0] != '\0') //오류 발생한 적없고, 결과값이 비어있지 않으면 결과값 출력.
	{
		for(i=0;i<k;i++)
		{
			if (i != k - 1)
				printf("%d ",result[i]);
			else
				printf("%d\n", result[i]);
		}
	}
	free(result);
	free(op);
	free(buf);
	}
}