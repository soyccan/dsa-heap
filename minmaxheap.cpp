#include "minmaxheap.h"

#ifdef _TEST
void MinMaxHeap::push(int key, int value)
{
    __list.push_back({key, value});
}

int MinMaxHeap::pop_max()
{
    auto p = std::max_element(__list.begin(), __list.end());
    int v = p->second;
    __list.erase(p);
    return v;
}

int MinMaxHeap::pop_min()
{
    auto p = std::min_element(__list.begin(), __list.end());
    int v = p->second;
    __list.erase(p);
    return v;
}

bool MinMaxHeap::empty() const
{
    return __list.empty();
}

size_t MinMaxHeap::size() const
{
    return __list.size();
}

#else

#endif
