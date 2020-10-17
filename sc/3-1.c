#include <stdio.h>

void print_day(int day) //요일과 날짜를 출력해주는 함수
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
    int tCase, day, poli, i, j, lost, k, p, r; //tCase = 테스트케이스 저장 변수, day = 전체 날짜 수, poli = 정당의 수, lost = 총 휴업일
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

        for(j=1; j<day+1; j++){ //날짜는 1부터 시작하기 때문에 1~day만큼 루프를 돈다.
            r = 0;
            for(k=0; k<poli; k++){ //정당의 수 만큼 루프를 돈다.
                if(j%hartal[k]==0){ //해당 정당의 휴업일일때,
                    if(!((j%7==1 || j%7==0) || (j%7==4))){ //일요일, 토요일, 수요일은 동맹휴업을 하지 않기로 하였음.
                        r++; //해당 정당 카운트
                        if (r >= (poli+1)/2) //해당 정당 수가 과반수로 정해지면
                        {
                            lost++; //쉬는날로 카운트
                            buf[p++]=j; //요일과 날짜를 출력해주기 위해 해당 날짜를 버퍼에 저장
                            r = 0;
                            break; //이미 정당의 수가 과반수를 넘겨 동맹휴업일로 지정되어 다음 정당을 고려하지 않기 위해 루프를 종료 시킨다.
                        }
                    }
                }
            }
        }

        printf("Lost: %d\n",lost); //총 동맹 휴업일 출력해준다.
        for (i=0;i<p;i++)
            print_day(buf[i]); //버퍼에 저장된 동맹휴업일의 요일과 날짜를 출력해준다.
		if (tCase!=0)
            printf("\n");
        lost = 0; //테스트케이스만큼 수행하기 위해 변수를 초기화시켜준다.
        p = 0;
    }
   return 0;
}