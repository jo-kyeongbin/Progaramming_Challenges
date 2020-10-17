#include <stdio.h>

int cyclehas(int n, int x)
{
    if (n == x) return 1;
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3*n + 1;
        if (n == x) return 1;
    }
    return 0;
}

int main(void)
{
    int n, x;

    while (scanf("%d %d", &n, &x) == 2) {
        if (cyclehas(n, x)) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
