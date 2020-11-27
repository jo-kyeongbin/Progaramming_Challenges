#include <stdio.h>
#define	abs(x) (((x)<0)?-(x):(x))
//10-1-1.input 3번 테스트케이스에 대해 잘못된 값을 출력하고, 해결하지 못하였다..
int arrsum(int *a, int alen) //해당 그룹의 원소(무게)의 합을 출력해주는 함수
{
    int i;
    int result=0;
    for(i=0;i<alen;i++) result = result+a[i];
    return result;
}

void swap(int *a, int *b) //원소의 자리를 바꿔주는 함수
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void tug(int *a, int *b, int alen, int blen)
{
    if (arrsum(a,alen)==arrsum(b,blen)) //몸무게 총합이 같을 경우 출력
    {
        printf("%d\n", arrsum(a,alen));
        printf("%d\n", arrsum(b,blen));
        return;
    }
    int tdiff;
    tdiff = arrsum(a,alen)-arrsum(b,blen);
    int i,j;
    for(i=0;i<alen;i++)
    {
        for(j=0;j<blen;j++)
        {
            if(abs(2*(b[j]-a[i])+tdiff)<abs(tdiff)) //해당 조건에 해당되는 a원소, b원소가 없다면 아래 if문에 의해 정답 출력.
            {
                swap(&a[i],&b[j]);
                tug(a,b,alen,blen);
                return;
            }
        }
    }
    if (arrsum(a,alen) > arrsum(b,blen)) //몸무게 총합이 다를 경우 작은 것부터 출력
        printf("%d %d\n",arrsum(b,blen), arrsum(a,alen));
    else
    {
        printf("%d %d\n",arrsum(a,alen), arrsum(b,blen));
    }
    return;
}

int main()
{
    int n,i,tcase;
    int a[50], b[50];
    scanf("%d",&tcase);
    getchar();
    while(tcase>0)
    {
        scanf("%d", &n);
        getchar();
        if (n%2==0) //짝수일 경우 반씩 나눠가진다.
        {
            for(i=0;i<n/2;i++) scanf("%d", &a[i]);
            for(i=0;i<n/2;i++) scanf("%d", &b[i]);
            tug(a,b,n/2,n/2);
        }
        else //홀수일 경우 a의 원소가 b원소보다 1개 더 많다.
        {
            for(i=0;i<(n+1)/2;i++) scanf("%d", &a[i]);
            for(i=0;i<(n-1)/2;i++) scanf("%d", &b[i]);
            tug(a,b,(n+1)/2,(n-1)/2);
        }
        tcase--;
        if(tcase>0)
            printf("\n");
    }
    return 0;
}
