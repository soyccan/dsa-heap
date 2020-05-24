#include <stdio.h>
#include <stdlib.h>

#include "../tools.h"

static const char* cmds[] = {"add", "quota", "drop", "print"};
static int nargs[] = {3, 2, 1, 1};

int main()
{
    srandomdev();

    int N = 10000, M = 1000000;
    printf("%d %d\n", N, M);
    while (M--) {
        int c = random() % 4;
        int j = random() % 1000000 - 500000;
        int p = j;
        int id = random() % N;
        int q = random() % 1000000 + 1;
        printf("%s ", cmds[c]);
        if (c == 0)
            printf("%d %d %d", j, p, id);
        else if (c == 1)
            printf("%d %d", q, id);
        else
            printf("%d", id);
        puts("");
    }
}
