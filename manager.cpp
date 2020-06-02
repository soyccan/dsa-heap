#include "manager.h"

#include <cstdio>


PrinterManager::PrinterManager(int num_printers)
{
    __num_printers = num_printers;
    __printers.resize(num_printers);
}

void PrinterManager::add(int job_id, int pri, int printer_id)
{
    __printers[printer_id].add(job_id, pri);
    printf("%d added to printer %d with priority %d\n", job_id, printer_id,
           pri);
}

void PrinterManager::quota(int q, int printer_id)
{
    __printers[printer_id].quota(q);
    printf("quota %d set for %d\n", q, printer_id);
}

void PrinterManager::drop(int printer_id)
{
    if (!__printers[printer_id].empty()) {
        __printers[printer_id].drop();
        printf("%d dropped on printer %d\n", job, printer_id);
    } else {
        printf("no jobs in %d\n", printer_id);
    }
}

void PrinterManager::print(int printer_id)
{
    if (!__printers[printer_id].empty()) {
        int job = __printers[printer_id].pop_max();
        printf("%d printed on printer %d\n", job, printer_id);
    } else {
        printf("no jobs in %d\n", printer_id);
    }
}
