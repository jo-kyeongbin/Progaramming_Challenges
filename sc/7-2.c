#include <stdio.h>


int chk[10];
char word[10];

void dfs(int depth,int len, char *input){
	int i;
	int before;
    if (depth == len){
        for (int i=0; i<len; ++i) printf("%c", word[i]);
        printf("\n");
        return;
    }
    before = -1;
    for (i=0; i<len; ++i){
        if (!chk[i] && (i == 0 || before != input[i])) {
            before = input[i];
            word[depth] = input[i];
            chk[i] = 1;
            dfs(depth + 1,len,input);
            chk[i] = 0;
        }
    }
}
 

void sort_input(char *input, int len)
{
	char temp;
	int i,j;
	int min;
	for(i=0;i<len;i++)
	{
		min = i;
		for(j=i+1;j<len;j++)
			if (input[j]<input[min]) min = j;
		temp = input[min];
		input[min] = input[i];
		input[i] = temp;
	}
}

int main() {
    char buf[1024];
	char input[10];
	int i = 0;
	int len = 0;
	while(fgets(buf,1024,stdin)!=NULL)
	{
		while(buf[i]!='\n'&&buf[i])
		{
			if (buf[i]>='a' && buf[i]<='z')
			{
				len++;
				input[len-1] = buf[i];
			}
			i++;
		}
		sort_input(input, len);
		dfs(0,len,input);
	}
    return 0;
}