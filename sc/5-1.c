#include <stdio.h>


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
			if(buf[i] & 0x80)
			{
				korean[j++] = buf[i++];
				korean[j++] = buf[i++];
				korean[j++] = buf[i++];
				kor++;
			}
			else
			{
				if (buf[i] != '\n')
				{
					english[k++] = buf[i++];
					eng++;
				}
				else
					i++;
			}
		}
		english[k] = '\0';
		korean[j] = '\0';
		printf("%s",english);
		printf("%s",korean);
		printf("\n");
		printf("%d %d %d\n",eng,kor,eng+kor);
	}
}