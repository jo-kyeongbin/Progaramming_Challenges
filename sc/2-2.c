#include <stdio.h>
#include <stdlib.h>

char* cmp_card(char *a)
{
	int count = 0;
	char *temp;
	int i,j;

	temp = (char*)malloc(sizeof(char) * 2);
	for (i=0;i<5;i++) // 앞에서부터 하나씩 비교해가면서 다음에 나올 문자가 현재와 같은 문자가 나오면 count를 증가시켜준다.
	{
		for (j=i+1;j<5;j++)
		{
			if (a[i] == a[j])
				count++;
		}
		if (temp[1] < (count + '0') || (temp[1] == (count + '0') && temp[0] < a[i]) || i == 0) //초기값이거나 더 큰 숫자를 가지거나, 같은 숫자인데 더 높은 알파벳을 가지면 temp에 저장한다.
		{
			temp[0] = a[i];
			temp[1] = count + '0';
		}
		count = 0;
	}
	return temp;
}

int main(){
	char input[12];
	char temp[5];
	char *value1;
	char *value2;
	int i;

	while (fgets(input, 12, stdin) != NULL)
	{
		for(i = 0 ;i < 5;i++)
			temp[i] = input[i]; //앞에 다섯장을 입력받는다.
		value1 = cmp_card(temp);
		for(i = 0;i < 5;i++)
			temp[i] = input[i+6]; //뒤에 다섯장을 입력받는다.
		value2 = cmp_card(temp);
		if (value1[1] > value2[1] || (value1[1] == value2[1] && value1[0] > value2[0])) //왼쪽(Tom)이 이기는 경우
			printf("Tom\n");
		else if (value1[1] < value2[1] || (value1[1] == value2[1] && value1[0] < value2[0])) //오른쪽(Jerry)가 이기는 경우
			printf("Jerry\n");
		else
			printf("Draw\n");
		getchar(); //버퍼를 비워주기 위해 수행, 수행하지 않으면 printf가 두번씩 수행된다.
		free(value1);
		free(value2);
	}
}