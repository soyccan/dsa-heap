#include "minmaxheap.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <utility>

#include "tools.h"


MinMaxHeap::MinMaxHeap()
{
    __heap.resize(1);  // index 0 is unused
}

void MinMaxHeap::push(int key, int value)
{
    __heap.emplace_back(key, value);
    __push_up(__heap.size() - 1);
}

int MinMaxHeap::pop_max()
{
    assert(!empty());
    assert(__heap.size() >= 1);
    int i;
    if (__heap.size() <= 2)
        i = 1;
    else if (__heap.size() <= 3)
        i = 2;
    else
        i = __heap[2].first > __heap[3].first ? 2 : 3;

    int ret = __heap[i].second;
    if (__heap.size() > i + 1) {
        __heap[i] = std::move(__heap.back());
        __heap.pop_back();
        __push_down_max(i);
    } else {
        __heap.pop_back();
    }
    return ret;
}

int MinMaxHeap::pop_min()
{
    assert(!empty());
    int ret = __heap[1].second;
    if (__heap.size() > 2) {
        __heap[1] = std::move(__heap.back());
        __heap.pop_back();
        __push_down_min(1);
    } else {
        __heap.pop_back();
    }
    return ret;
}

bool MinMaxHeap::empty() const
{
    assert(__heap.size() >= 1);
    return __heap.size() <= 1;
}

size_t MinMaxHeap::size() const
{
    assert(__heap.size() >= 1);
    return __heap.size() - 1;
}

inline bool MinMaxHeap::__has_child(int i) const
{
    assert(__heap.size() >= 1);
    assert(i >= 1 && i < __heap.size());

    // TODO :overflow
    return i << 1 < __heap.size() || (i << 1) + 1 < __heap.size();
}

template <typename Compare>
inline void MinMaxHeap::__push_down_base(int i, Compare comp)
{
    while (__has_child(i)) {
        int m = i;
        int flag = 0;  // child=1, grandchild=2
        // TODO: overflow
        for (int j = i << 1; j < __heap.size() && j <= (i << 1) + 1; j++) {
            // child of i
            if (comp(__heap[j], __heap[m])) {
                // TODO: save __heap[m] in a local variable for performance?
                m = j;
                flag = 1;
            }
        }
        for (int j = i << 2; j < __heap.size() && j <= (i << 2) + 3; j++) {
            // grandchlid of i
            if (comp(__heap[j], __heap[m])) {
                m = j;
                flag = 2;
            }
        }

        if (flag == 1) {
            // min/max is among child
            std::swap(__heap[m], __heap[i]);

        } else if (flag == 2) {
            // min/max is among grandchild
            std::swap(__heap[m], __heap[i]);

            if (comp(__heap[m >> 1], __heap[m])) {
                std::swap(__heap[m >> 1], __heap[m]);
            }

        } else {
            // i is already min/max
            break;
        }
        i = m;
    }
}

inline void MinMaxHeap::__push_down_min(int i)
{
    __push_down_base(i, std::less());
}

inline void MinMaxHeap::__push_down_max(int i)
{
    __push_down_base(i, std::greater());
}

inline bool MinMaxHeap::__is_root(int i) const
{
    assert(__heap.size() >= 1);
    assert(i >= 1 && i < __heap.size());

    return i == 1;
}

inline void MinMaxHeap::__push_up(int i)
{
    if (!__is_root(i)) {
        if (__builtin_clz(i) & 1) {
            // min level
            if (__heap[i] > __heap[i >> 1]) {
                std::swap(__heap[i], __heap[i >> 1]);
                __push_up_max(i >> 1);
            } else {
                __push_up_min(i);
            }
        } else {
            // max level
            if (__heap[i] < __heap[i >> 1]) {
                std::swap(__heap[i], __heap[i >> 1]);
                __push_up_min(i >> 1);
            } else {
                __push_up_max(i);
            }
        }
    }
}

inline bool MinMaxHeap::__has_grandparent(int i) const
{
    assert(i >= 1 && i < __heap.size());
    assert(__heap.size() >= 1);

    return !__is_root(i) && !__is_root(i >> 1);
}

template <typename Compare>
inline void MinMaxHeap::__push_up_base(int i, Compare comp)
{
    while (__has_grandparent(i) && comp(__heap[i], __heap[i >> 2])) {
        std::swap(__heap[i], __heap[i >> 2]);
        i >>= 2;
    }
}

inline void MinMaxHeap::__push_up_min(int i)
{
    __push_up_base(i, std::less());
}

inline void MinMaxHeap::__push_up_max(int i)
{
    __push_up_base(i, std::greater());
}

void MinMaxHeap::dump_container() const
{
    LOGN("  container: ");
    for (auto p : __heap) {
        LOGN("(%d,%d) ", p.first, p.second);
    }
    LOG("");
}
