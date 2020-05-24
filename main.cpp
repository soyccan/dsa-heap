#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "minmaxheap.h"
#include "tools.h"

#define EQ(s1, s2) (strncmp(s1, s2, sizeof(s1)) == 0)
#define INVAL(msg)                                                        \
    {                                                                     \
        fprintf(stderr, "\e[31mERROR\e[0m: invalid argument: %s\n", msg); \
        exit(255);                                                        \
    }
#define PARSE_ARGS(identifier, num, str, fmt, ...)            \
    {                                                         \
        if (sscanf(str, fmt, ##__VA_ARGS__) != (num))         \
            INVAL(identifier " requires " #num " arguments"); \
    }


static int N, M;
static std::vector<MinMaxHeap> jobs;
static std::vector<int> quotas;


void drop(int printer_id)
{
    if (!jobs[printer_id].empty()) {
        int job = jobs[printer_id].pop_min();
        printf("%d dropped on printer %d\n", job, printer_id);
    } else {
        printf("no jobs in %d\n", printer_id);
    }
}

void add(int job_id, int pri, int printer_id)
{
    if (jobs[printer_id].size() == quotas[printer_id])
        drop(printer_id);
    assert(jobs[printer_id].size() + 1 <= quotas[printer_id]);
    jobs[printer_id].push(pri, job_id);
    printf("%d added to printer %d with priority %d\n", job_id, printer_id,
           pri);
}

void quota(int q, int printer_id)
{
    while (jobs[printer_id].size() > q)
        drop(printer_id);
    quotas[printer_id] = q;
    printf("quota %d set for %d\n", q, printer_id);
}

void print(int printer_id)
{
    if (!jobs[printer_id].empty()) {
        int job = jobs[printer_id].pop_max();
        printf("%d printed on printer %d\n", job, printer_id);
    } else {
        printf("no jobs in %d\n", printer_id);
    }
}

void init(int num_printers)
{
    quotas.resize(num_printers);
    jobs.resize(num_printers);
    FOR (int, i, 0, N) {
        quotas[i] = M;
    }
}

int main()
{
    char line[48];
    char cmd[16];
    int job_id, pri, printer_id, q;
    fgets(line, sizeof line, stdin);
    PARSE_ARGS("N, M", 2, line, "%d %d", &N, &M);
    init(N);
    FOR (int, cmdi, 0, M) {
        fgets(line, sizeof line, stdin);
        // LOGN("  read: %s", line);
        char* pline = line;
        char* pcmd = strsep(&pline, " ");
        memcpy(cmd, pcmd, sizeof cmd);  // TODO: vs. strncpy

        if (EQ(cmd, "add")) {
            PARSE_ARGS("add", 3, pline, "%d %d %d", &job_id, &pri, &printer_id);
            add(job_id, pri, printer_id);

        } else if (EQ(cmd, "quota")) {
            PARSE_ARGS("quota", 2, pline, "%d %d", &q, &printer_id);
            quota(q, printer_id);

        } else if (EQ(cmd, "drop")) {
            PARSE_ARGS("drop", 1, pline, "%d", &printer_id);
            drop(printer_id);

        } else if (EQ(cmd, "print")) {
            PARSE_ARGS("print", 1, pline, "%d", &printer_id);
            print(printer_id);

        } else {
            INVAL(("unrecognized command: " + std::string(cmd)).c_str());
        }

        // jobs[printer_id].dump_container();
    }
    return 0;
}
