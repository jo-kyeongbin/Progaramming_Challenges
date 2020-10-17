#include <stdio.h>
#define BUFSIZE 1024

int main() {
	int i;
	int temp;
	int temp2;
	int key;
	char cal;
	char n[BUFSIZE];
	
	while (fgets(n, BUFSIZE, stdin) != NULL){
		if (!('A' <= n[0] && 'J' >= n[0]))	//주어진 문자가 아닐 경우에 error를 출력한다.
		{
			printf("Error\n");
			continue;
		}
		i = 0;
		temp = 0;
		key = 0;
		while (n[i])
		{
			if ('A' <= n[i] && n[i] <= 'J' && key == 0) //key를 두어서 연산자와 피연산자를 구분하였다.
			{
				temp = temp * 10 + (n[i++] - 65); //65는 대문자 A의 아스키코드이며, 65를 빼면 숫자가 된다.
				continue;
			}
			else if (!('A' <= n[i] && n[i] <= 'J') && n[i] != '\n') //만약에 연산자라면, \n은 fgets 특성상 개행도 읽기 때문이다.
			{
				if (!('A' <= n[i - 1] && n[i - 1] <= 'J')) // 앞에 연산자가 나왔는데 전에 온 문자가 피연산자가 아니라면 에러.
				{
					printf("Error\n");
					key = -1; //에러가 발생하면 와일문을 종료한다. 그리고 밑에서 출력을 방지해주기 위해 key를 -1로 둔다.
					break;
				}
				key = 1;	//key 값이 1이기 때문에 temp의 값이 변하지 않는다.
				cal = n[i++];	//연산자를 저장해준다.
				if (n[i] == '\n')	//앞에서 i++을 했기에 \n일수도 있고, 연산자 이후 피연산자가 나오지 않았으므로 에러처리
				{
					printf("Error\n");
					key = -1;
				}
				temp2 = 0;
				continue;	//다시 while문 수행하면 아래에서 temp2 초기화를 시작한다. (temp1 연산자 temp2 순서)
			}
			else if (key == 1 && ('A' <= n[i] && n[i] <= 'J'))
			{
				temp2 = temp2 * 10 + (n[i++] - 65);
				if (!('A' <= n[i] && n[i] <= 'J')) //i++을 해주었기 때문에 연산자일수도 있다. 연산자라면 연산을 수행한다.
				{
					if (cal == 'S')
						temp = temp - temp2;
					if (cal == 'T')
						temp = temp * temp2;
					if (cal == 'V')
					{
						if (temp2 == 0) //0으로 나누는 경우는 에러처리 한다.
						{
							printf("Error\n");
							key = -1;
							break;
						}
						temp = temp / temp2;
					}
					if (cal == 'P')
						temp = temp + temp2;
				} //temp의 값이 temp2와 연산을 수행한 결과로 바뀌게 된다. (계속 누적된다.)
				continue;
			}
			if (n[i] == '\n') //while문은 \n가 나오거나 널문자가 나오면 종료된다.
				break;
		}
	if (key != -1)
		printf("%d\n",temp); //에러가 나온 경우가 아니라면 temp의 값을 출력해준다.
	}
}