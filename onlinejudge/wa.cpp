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

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <utility>

/* convinient functions */
#ifndef _DSA_TOOLS_H_
#define _DSA_TOOLS_H_ 1

#include <cstdio>

/* debug only */
#ifndef NDEBUG
#define LOG(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__);
#define LOGN(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__);
#else
#define LOG(...)
#define LOGN(...)
#endif
/* end debug only */


#define FOR(type, i, start, end) for (type i = (start); i < (end); i++)

#endif


MinMaxHeap::MinMaxHeap()
{
    __heap.resize(1);  // index 0 is unused
    __heap.reserve(1000000);
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
    size_t i;
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

inline bool MinMaxHeap::__has_child(size_t i) const
{
    assert(__heap.size() >= 1);
    assert(i >= 1 && i < __heap.size());

    // TODO :overflow
    return i << 1 < __heap.size() || (i << 1) + 1 < __heap.size();
}

template <typename Compare>
inline void MinMaxHeap::__push_down_base(size_t i, Compare comp)
{
    while (__has_child(i)) {
        size_t m = i;
        int flag = 0;  // child=1, grandchild=2
        // TODO: overflow
        for (size_t j = i << 1; j < __heap.size() && j <= (i << 1) + 1; j++) {
            // child of i
            if (comp(__heap[j], __heap[m])) {
                // TODO: save __heap[m] in a local variable for performance?
                m = j;
                flag = 1;
            }
        }
        for (size_t j = i << 2; j < __heap.size() && j <= (i << 2) + 3; j++) {
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

inline void MinMaxHeap::__push_down_min(size_t i)
{
    __push_down_base(i, std::less<std::pair<int, int>>());
}

inline void MinMaxHeap::__push_down_max(size_t i)
{
    __push_down_base(i, std::greater<std::pair<int, int>>());
}

inline bool MinMaxHeap::__is_root(size_t i) const
{
    assert(__heap.size() >= 1);
    assert(i >= 1 && i < __heap.size());

    return i == 1;
}

inline void MinMaxHeap::__push_up(size_t i)
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

inline bool MinMaxHeap::__has_grandparent(size_t i) const
{
    assert(i >= 1 && i < __heap.size());
    assert(__heap.size() >= 1);

    return !__is_root(i) && !__is_root(i >> 1);
}

template <typename Compare>
inline void MinMaxHeap::__push_up_base(size_t i, Compare comp)
{
    while (__has_grandparent(i) && comp(__heap[i], __heap[i >> 2])) {
        std::swap(__heap[i], __heap[i >> 2]);
        i >>= 2;
    }
}

inline void MinMaxHeap::__push_up_min(size_t i)
{
    __push_up_base(i, std::less<std::pair<int, int>>());
}

inline void MinMaxHeap::__push_up_max(size_t i)
{
    __push_up_base(i, std::greater<std::pair<int, int>>());
}

void MinMaxHeap::dump_container() const
{
    LOGN("  container: ");
    for (auto p : __heap) {
        LOGN("(%d,%d) ", p.first, p.second);
    }
    LOG("");
}

#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

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

int main()
{
    int a, b;
    MinMaxHeap h;
    while (scanf("%d", &a) != EOF) {
        if (a == 1) {
            scanf("%d", &b);
            h.push(b, b);

        } else if (a == 2) {
            printf("%d\n", h.pop_max());

        } else {
            printf("%d\n", h.pop_min());
        }
    }
    return 0;
}
