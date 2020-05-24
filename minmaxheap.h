#ifndef _DSA_MINMAXHEAP_H_
#define _DSA_MINMAXHEAP_H_ 1

#include <algorithm>
#include <list>
#include <utility>
#include <vector>

class MinMaxHeap
{
public:
    MinMaxHeap();
    void push(int key, int value);
    int pop_max();
    int pop_min();

    bool empty() const;
    size_t size() const;

    void dump_container() const;

private:
#ifdef _STABLE
    std::list<std::pair<int, int>> __list;

#else
    template <typename Compare>
    void __push_down_base(int i, Compare comp);

    void __push_down_min(int i);
    void __push_down_max(int i);

    template <typename Compare>
    void __push_up_base(int i, Compare comp);

    void __push_up_min(int i);
    void __push_up_max(int i);
    void __push_up(int i);

    bool __has_child(int i) const;
    bool __is_root(int i) const;
    bool __has_grandparent(int i) const;

    // TODO: pair is not a good container for comparing key
    std::vector<std::pair<int, int>> __heap;
#endif  // _STABLE
};

#endif
