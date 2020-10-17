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