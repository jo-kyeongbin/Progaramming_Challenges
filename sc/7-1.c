#include <stdio.h>

void print_subset(int *set, int n) {

        int i;
        printf("{ ");
        for (i = 0;i < n-1;++i)
               printf("%d ", set[i]);
        printf("%d }\n", set[n-1]);
}

void powerset(int *set, int n, int k, int m, int r) {
        if (n - k < m - r) return;
        if (r == m) {
               print_subset(set, m);
               return;
        }
        set[r] = k+1;
        powerset(set, n, k+1, m, r+1);
        powerset(set, n, k+1, m, r);
}

int main() {

	int i;
	char buf[1024];
	int set[1024] = {0,};
	int len;
	while (fgets(buf,1024,stdin)!=NULL)
	{
		i = 0;
		len = 0;
		while(buf[i]!='\n'&&buf[i])
		{
			if (buf[i]>='0' && buf[i] <= '9')
				len++;
			i++;
		}

        printf("{ }\n");
        for (i = 1;i<len+1;++i)
               powerset(set, len, 0, i, 0);
	}
    return 0;
}
