#ifndef _DSA_PRINTER_H_
#define _DSA_PRINTER_H_ 1

#include "minmaxheap.h"
#include "tools.h"

class Printer
{
public:
    Printer(int id);

    void add(int job_id, int pri);
    void quota(int q);
    void drop();
    void print();

private:
    int __id;
    int __quota;
    MinMaxHeap __jobs;
};

#endif
