#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int pmf[] = {8000, 1000, 1000, 0};
static int cmf[4];

int main()
{
    srandom(time(NULL));

    cmf[0] = pmf[0];
    for (int i = 1; i < 4; i++)
        cmf[i] = cmf[i - 1] + pmf[i];

    int N = 1, M = 10000000;
    int sz = 0;
    while (M--) {
        int c = random() % cmf[3];
        int j = random() % 1000000 - 500000;
        if (c < cmf[0] || sz == 0) {
            printf("1 %d\n", j);
            sz++;
        } else if (c < cmf[1]) {
            puts("2");
            sz--;
        } else if (c < cmf[2]) {
            puts("3");
            sz--;
        } else
            ;
    }
}
