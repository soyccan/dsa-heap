#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char* cmds[] = {"add", "quota", "drop", "print"};
static int pmf[] = {1000, 0, 0, 0};
static int cmf[4];
static int nargs[] = {3, 2, 1, 1};

int main()
{
    srandom(time(NULL));

    cmf[0] = pmf[0];
    for (int i = 1; i < 4; i++)
        cmf[i] = cmf[i - 1] + pmf[i];

    int N = 1000000, M = 1000000;
    printf("%d %d\n", N, M);
    while (M--) {
        int c = random() % cmf[3];
        int j = random() % 1000000 - 500000;
        int p = j;
        int id = random() % N;
        int q = random() % 1000000 + 1;
        if (c < cmf[0])
            printf("add %d %d %d", j, p, id);
        else if (c < cmf[1])
            printf("quota %d %d", q, id);
        else if (c < cmf[2])
            printf("drop %d", id);
        else
            printf("print %d", id);
        puts("");
    }
}
