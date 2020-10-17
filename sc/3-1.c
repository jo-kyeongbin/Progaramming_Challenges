#include <stdio.h>

void print_day(int day)
{
    int result = day % 7;

    switch (result)
    {
        case 1:
            printf("Sun: %d\n",day);
            break;
        case 2:
            printf("Mon: %d\n",day);
            break;
        case 3:
            printf("Tue: %d\n",day);
            break;
        case 4:
            printf("Wed: %d\n",day);
            break;
        case 5:
            printf("Thu: %d\n",day);
            break;
        case 6:
            printf("Fri: %d\n",day);
            break;
        case 0:
            printf("Sat: %d\n",day);
            break;
    }
}


int main() {
    int tCase, day, poli, i, j,lost,k,p,r;
    int buf[1024];
    lost = 0;
    p = 0;
    scanf("%d",&tCase);



    while(tCase--){
        scanf("%d",&day);
        scanf("%d",&poli);


        int hartal[poli];
        
        for(i=0; i<poli; i++){
            scanf("%d",&hartal[i]);
        }

        for(j=1; j<day+1; j++){
            r = 0;
            for(k=0; k<poli; k++){
                if(j%hartal[k]==0){
                    if(!((j%7==1 || j%7==0) || (j%7==4))){
                        r++;
                        if (r >= (poli+1)/2)
                        {
                            lost++;
                            buf[p++]=j;
                            r = 0;
                            break;
                        }
                    }
                }
            }
        }

        printf("Lost: %d\n",lost);
        for (i=0;i<p;i++)
            print_day(buf[i]);
		printf("\n");
        lost = 0;
        p = 0;
    }

   return 0;
}