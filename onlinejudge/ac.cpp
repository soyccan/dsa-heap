// http://mypaper.pchome.com.tw/zerojudge/post/1322053037
// https://zerojudge.tw/ShowProblem?problemid=a091
#include <stdio.h>
#include <stdlib.h>
struct Deap {
    int V;
} Deap[10000005], T;
int L = 1;

int Judge(int p)
{
    while (p > 3)
        p /= 2;
    return p; /*2 left-min heap 3 right-max heap*/
}
int MinPartner(int p)
{
    int i = p, s = 1;
    while (p > 3)
        p /= 2, s *= 2;
    return i - s;
}
int MaxPartner(int p)
{
    if (p == 2)
        return 2;
    int i = p, s = 1;
    while (p > 3)
        p /= 2, s *= 2;
    if (i + s > L)
        return (i + s) / 2;
    return i + s;
}
void MinInsert(int S, int N)
{
    int P = S / 2;
    while (P > 1 && Deap[P].V > N)
        Deap[S].V = Deap[P].V, S = P, P = S / 2;
    Deap[S].V = N;
}
void MaxInsert(int S, int N)
{
    int P = S / 2;
    while (P > 1 && Deap[P].V < N)
        Deap[S].V = Deap[P].V, S = P, P = S / 2;
    Deap[S].V = N;
}
void Deap_Insert(int N)
{
    L++;
    if (L == 2) {
        Deap[2].V = N;
        return;
    }
    int p = L, i;
    switch (Judge(p)) {
    case 3: /*right */
        i = MinPartner(p);
        if (N < Deap[i].V)
            Deap[p].V = Deap[i].V, MinInsert(i, N);
        else
            MaxInsert(p, N);
        break;
    case 2: /*left */
        i = MaxPartner(p);
        if (N > Deap[i].V)
            Deap[p].V = Deap[i].V, MaxInsert(i, N);
        else
            MinInsert(p, N);
        break;
    }
}
void Delete_Max()
{
    int p = L, t = Deap[L--].V, a, b, i;
    for (a = 3; a * 2 <= L; a = b) {
        a *= 2;
        if (a < L && Deap[a].V < Deap[a + 1].V)
            b = a + 1;
        else
            b = a;
        Deap[a / 2].V = Deap[b].V;
    }

    i = MinPartner(a);
    int biggest = i;
    if (2 * i <= L) {
        biggest = 2 * i;
        if (((2 * i + 1) <= L) && (Deap[2 * i].V < Deap[2 * i + 1].V))
            biggest++;
    }
    if (t < Deap[biggest].V) {
        Deap[a].V = Deap[biggest].V;
        MinInsert(biggest, t);
    } else
        MaxInsert(a, t);
}
void Delete_Min()
{
    int p = L, t = Deap[L--].V, a, b, i;
    for (a = 2; a * 2 <= L; a = b) {
        a *= 2;
        if (a < L && Deap[a].V > Deap[a + 1].V)
            b = a + 1;
        else
            b = a;
        Deap[a / 2].V = Deap[b].V;
    }
    i = MaxPartner(a);
    if (t > Deap[i].V) {
        Deap[a] = Deap[i];
        MaxInsert(i, t);
    } else
        MinInsert(a, t);
}
main()
{
    static int D, N, a;
    while (scanf("%d", &D) == 1) {
        switch (D) {
        case 1:
            scanf("%d", &N), Deap_Insert(N);
            break;
        case 2:
            printf("%d\n", (L == 2) ? Deap[2].V : Deap[3].V);
            if (L == 2)
                Delete_Min();
            else
                Delete_Max();
            break;
        case 3:
            printf("%d\n", Deap[2].V), Delete_Min();
            break;
        }
    }
    return 0;
}
