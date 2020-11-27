#include <stdio.h>
#define	abs(x) (((x)<0)?-(x):(x))

int arrsum(int *a, int alen)
{
    int i;
    int result=0;
    for(i=0;i<alen;i++) result = result+a[i];
    return result;
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void tug(int *a, int *b, int alen, int blen)
{
    if (arrsum(a,alen)==arrsum(b,blen))
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
            if(abs(2*(b[j]-a[i])+tdiff)<abs(tdiff))
            {
                swap(&a[i],&b[j]);
                tug(a,b,alen,blen);
                return;
            }
        }
    }
    if (arrsum(a,alen) > arrsum(b,blen))
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
        if (n%2==0)
        {
            for(i=0;i<n/2;i++) scanf("%d", &a[i]);
            for(i=0;i<n/2;i++) scanf("%d", &b[i]);
            tug(a,b,n/2,n/2);
        }
        else
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
