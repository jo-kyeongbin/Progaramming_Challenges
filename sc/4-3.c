#include <stdio.h>

int atoi(char *s)
{
	int i = 0;
	int result = 0;
	while (s[i] != '\n' && s[i] != ' ')
		result = (result * 10) + (s[i++] - '0');
	return (result);
}

int main()
{
	char testcase[12];
	int count = 0;
	char line[256];
	int i,j,k;
	int row, col;
	char buf[51][51];
	char buf_line[52];
	char mn[7];

	while(fgets(testcase,12,stdin)!=NULL)
	{
		count = atoi(testcase);
		while(count)
		{
			fgets(line,256,stdin);
			scanf("%d %d[^\n]", &row, &col);
			for (i=0;i<row;i++)
			{
				fgets(buf_line,52,stdin);
				for(j=0;j<col;j++)
					buf[i][j] = buf_line[j];
				buf[i][j] = 0;
				printf("%d : %s\n",i,buf[i]);
			}
			count = 0;
		}
	}
}