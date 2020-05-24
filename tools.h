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
