#ifndef __SVECTOR_H__
#define __SVECTOR_H__


#include <stdbool.h>
#include <stddef.h>

#define SVECTOR_INSERT(type, vecptr, literal, idx) \
    do {type tmp = (literal); SVector_insert((vecptr), &tmp, (idx));} while(false)

#define SVECTOR_PUSH(type, vecptr, literal) \
    do {type tmp = (literal); SVector_push((vecptr), &tmp);} while(false)


typedef struct SVectorStr_def{
    void* data;
    size_t count;
    size_t capacity;
    size_t element_size;
} SVector;


void SVector_init(SVector* vec, size_t element_size, size_t cap);
void SVector_free(SVector* vec);
bool SVector_recapacity(SVector* vec, size_t new_cap);

bool SVector_insert(SVector* vec, void* element, size_t idx);
void SVector_push(SVector* vec, void* element);
bool SVector_remove(SVector* vec, size_t idx, void* removed_el);
bool SVector_pop(SVector* vec, void* popped_el);


#endif //__SVECTOR_H__
