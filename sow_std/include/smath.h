#ifndef __MATH_H__
#define __MATH_H__

#include <stdbool.h>


#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define MAX(type, data, count, output) \
    do { \
        if ((count) == 0){ \
            output = 0;\
        } \
        type mx = (data)[0];\
        size_t i = 1; \
        while (i < count){ \
            type p = (data)[i];\
            if (p > mx) {\
                mx = p; \
            } \
            ++i; \
        } \
        output = mx; \
    } while(false)


#define MIN(type, data, count, output) \
    do { \
        if ((count) == 0){ \
            output = 0;\
        } \
        type mn = (data)[0];\
        size_t i = 1; \
        while (i < count){ \
            type p = (data)[i];\
            if (p < mn) {\
                mn = p; \
            } \
            ++i; \
        } \
        output = mn; \
    } while(false)

#define SUM(type, data, count, output)\
    do { \
        output = 0; \
        for(size_t i=0; i<count; ++i){ \
            type c = data[i]; \
            output += c; \
        } \
    } while(false)

#endif //__MATH_H__
