#include <stdio.h>

typedef struct word{
	int index;
	int number; // aabbcc = 222, abbc = 121
}word;

int my_atoi(char *s)
{
	int result = 0;
	while(*s)
	{
		result = result * 10 + (*s - '0');
		s++;
	}
	return result;
}

void get_data(char *sequence, struct word *data)
{
	int i = 0;
	int k = 0;
	int j;
	int l;
	int index;
	char numbers[100];
	int map[256] = {0,};
	int value;
	while(sequence[i])
	{
		value = 1;
		index = i;
		while (!(sequence[index] >= 'a' && sequence[index] <= 'z'))
			index++;
		data[k].index = index;
		j = 0;
		while(sequence[i] != ' ' && sequence[i] != '\n' && sequence[i])
		{
			if (map[sequence[i]]==0 && sequence[i] != '0')
				map[sequence[i]] = value++;
			numbers[j++] = map[sequence[i]] + '0';
			i++;
		}
		for(l=0;l<256;l++)
			map[l]=0;
		numbers[j] = '\0';
		data[k++].number = my_atoi(numbers);
		i++;
	}
}

void remove_it(char *text, char c)
{
	int k = 0;
	while(text[k]!='\n' && text[k])
	{
		if (text[k] == c)
			text[k] = '0';
		k++;
	}
}

void init_mapping(char cipher_c, char plain_c, char *cipher, char *plain, char *map)
{
	int c_index = 0;
	int p_index = 0;
	while(cipher[c_index]!='\n' && cipher[c_index])
	{
		if (cipher[c_index] == cipher_c)
		{
			while(cipher[c_index]!=' ' && c_index != 0)
				c_index--;
			if (c_index != 0)
				c_index++;
			break;
		}
		c_index++;
	}
	while(plain[p_index]!='\n' && plain[p_index])
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
	while(plain[p_index]>='a' && plain[p_index] <= 'z')
	{
		map[plain[p_index]] = cipher[c_index];
		plain[p_index] = '0';
		cipher[c_index] = '0';
		p_index++;
		c_index++;
	}
}

int validation(struct word *plain_data, char plain_c, char *plain)
{
	int i=0,k=0;
	int count = 0;
	int exist[10] = {0,};
	while(plain[i]!='\n')
	{
		i = plain_data[k].index;
		while(plain[i] != ' ' && plain[i] != '\n')
		{
			if(plain[i] == plain_c)
			{	
				exist[k] = 1;
				break;
			}
			i++;
		}
		k++;
	}
	while(k>=0)
	{
		if (exist[k] == 1)
			count++;
		k--;
	}
	if (count == 0)
		return 0;
	if (count > 1)
		return -1;
	return 1;
}

int main()
{
	char map[256];
	char sen[44] = "the quick brown fox jumps over the lazy dog";
	char buf[1024];
	char plain[1024];
	char cipher[1024];
	word plain_data[10];
	word cipher_data[10];
	int i,word,k,count,c_index,p_index,key=1;

	while (fgets(buf,1024,stdin)!=NULL)
	{
		scanf("%d",&word);
		getchar();
		fgets(plain,1024,stdin);
		fgets(cipher,1024,stdin);
		get_data(plain,plain_data);
		i = 0;
		while(buf[i]!='\n')
		{
			if(buf[i]=='?')
			{
				i++;
				continue;
			}
			else
			{
				if(buf[i]!=' ')
				{
					map[sen[i]] = buf[i]; //map[평문] = 암호문;
					if(validation(plain_data,sen[i],plain) == 1)
						init_mapping(buf[i], sen[i], cipher, plain, map);
					if(validation(plain_data,sen[i],plain) != 0)
					{
						remove_it(plain,sen[i]);
						remove_it(cipher,buf[i]);
					}
				}
				i++;
			}
		}
		get_data(plain, plain_data);
		get_data(cipher,cipher_data);
		while(key==1)
		{
			for(i=0;i<word;i++)
			{
				count = 0;
				for(k=0;k<word;k++)
				{
					if(plain_data[i].number == cipher_data[k].number && plain_data[i].number != 0)
					{
						count++;
						c_index = cipher_data[k].index;
					}
				}
				if(count == 1)
				{
					p_index = plain_data[i].index;
					while(plain[p_index] != ' ' && plain[p_index] != '\n')
					{
						map[plain[p_index]] = cipher[c_index];
						remove_it(plain,plain[p_index]);
						remove_it(cipher,cipher[c_index]);
						p_index++;
						c_index++;
					}
				}
			}
			i = 0;
			while(plain[i])
			{
				if(plain[i]>='a' && plain[i] <= 'z')
					break;
				i++;
			}
			if(plain[i] == '\0')
				key = 0;
			else
			{
				get_data(plain,plain_data);
				get_data(cipher,cipher_data);
			}
		}
		for(i=0;i<44;i++)
		{
			if(sen[i]>='a' && sen[i] <= 'z')
				printf("%c",map[sen[i]]);
			if(sen[i] == ' ')
				printf(" ");
		}
		printf("\n");
		/*for(i='a';i<='z';i++)
			printf("%c -> %c\n",i,map[i]);*/
	}
}