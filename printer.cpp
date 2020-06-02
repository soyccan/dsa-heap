#include "printer.h"

#include <cstdio>


Printer::Printer(int id) : __id(id), __quota(0) {}

void Printer::add(int job_id, int pri)
{
    if (__jobs.size() == __quota)
        drop();
    assert(__jobs.size() + 1 <= __quota);
    __jobs.push(pri, job_id);
    printf("%d added to printer %d with priority %d\n", job_id, __id, pri);
}

void Printer::quota(int q)
{
    while (__jobs.size() > q)
        drop();
    __quota = q;
    printf("quota %d set for %d\n", q, __id);
}

void Printer::drop()
{
    if (!__jobs.empty()) {
        int job = __jobs.pop_min();
        printf("%d dropped on printer %d\n", job, __id);
    } else {
        printf("no jobs in %d\n", __id);
    }
}

void Printer::print()
{
    if (!__jobs.empty()) {
        int job = __jobs.pop_max();
        printf("%d printed on printer %d\n", job, __id);
    } else {
        printf("no jobs in %d\n", __id);
    }
}
