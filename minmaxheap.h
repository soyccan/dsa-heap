#ifndef _DSA_MINMAXHEAP_H_
#define _DSA_MINMAXHEAP_H_ 1

#ifdef _TEST
#include <algorithm>
#include <list>
#include <utility>

class MinMaxHeap
{
public:
    void push(int key, int value);
    int pop_max();
    int pop_min();

    bool empty() const;
    size_t size() const;

private:
    std::list<std::pair<int, int>> __list;
};

#else

#include <cstddef>

class MinMaxHeap
{
public:
    void push(int key, int value);
    int pop_max();
    int pop_min();

    bool empty() const;
    size_t size() const;
};

#endif  // _TEST

#endif
