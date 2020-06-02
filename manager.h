#ifndef _DSA_MANAGER_H_
#define _DSA_MANAGER_H_ 1

#include <vector>

#include "minmaxheap.h"

class PrinterManager
{
public:
    PrinterManager(int num_printers = 0);
    void add(int job_id, int pri, int printer_id);
    void quota(int q, int printer_id);
    void drop(int printer_id);
    void print(int printer_id);

private:
    int __num_printers;
    std::vector<Printer> __printers;
};

#endif
