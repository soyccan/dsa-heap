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
    void __push_down_base(size_t i, Compare comp);

    void __push_down_min(size_t i);
    void __push_down_max(size_t i);

    template <typename Compare>
    void __push_up_base(size_t i, Compare comp);

    void __push_up_min(size_t i);
    void __push_up_max(size_t i);
    void __push_up(size_t i);

    bool __has_child(size_t i) const;
    bool __is_root(size_t i) const;
    bool __has_grandparent(size_t i) const;

    // TODO: pair is not a good container for comparing key
    std::vector<std::pair<int, int>> __heap;
#endif  // _STABLE
};

#endif
