#ifndef __SVECTORSTR_H__
#define __SVECTORSTR_H__

//This is a vector for string. because strings in C are tricky

#include <stdbool.h>
#include <stddef.h>

typedef struct SVector_def{
    char** data;
    size_t count;
    size_t capacity;
} SVectorStr;


void SVectorStr_init(SVectorStr* vec, size_t cap);
void SVectorStr_free(SVectorStr* vec);
bool SVectorStr_recapacity(SVectorStr* vec, size_t new_cap);

bool SVectorStr_insert(SVectorStr* vec, const char* element, size_t idx);
void SVectorStr_push(SVectorStr* vec, const char* element);
bool SVectorStr_remove(SVectorStr* vec, size_t idx);
bool SVectorStr_pop(SVectorStr* vec);

//join all string in the vector into one string. you need to call free on that string by your own
char* SVectorStr_join(SVectorStr* vec);


#endif //__SVECTORSTR_H__
