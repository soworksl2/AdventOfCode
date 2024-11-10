#include "svector.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define GROW_FACTOR 2


static void SVector_ensure_capacity(SVector* vec){
    if (vec->count < vec->capacity){
        return;
    }

    SVector_recapacity(vec, vec->capacity * GROW_FACTOR);
}




void SVector_init(SVector* vec, size_t element_size, size_t cap){
    vec->count = 0;
    vec->capacity = cap;
    vec->element_size = element_size;
    vec->data = malloc(element_size * cap);
}

void SVector_free(SVector* vec){
    vec->count = 0;
    vec->capacity = 0;
    vec->element_size = 0;
    free(vec->data);
    vec->data = NULL;
}

bool SVector_recapacity(SVector* vec, size_t new_cap){
    if (vec->count > new_cap){
        return false;
    }

    void* new_data = realloc(vec->data, vec->element_size * new_cap);
    vec->capacity = new_cap;
    vec->data = new_data;
    return true;
}


bool SVector_insert(SVector* vec, void* element, size_t idx){
    if (idx > vec->count){
        return false;
    }

    SVector_ensure_capacity(vec);

    void* slot_ptr = ((char*)vec->data) + (idx * vec->element_size);
    if (idx == vec->count){
        memcpy(slot_ptr, element, vec->element_size);
        vec->count++;
        return true;
    }
    
    size_t el2mov = vec->count - idx;
    void* advanced_ptr = ((char*)slot_ptr) + (1 * vec->element_size);
    memmove(advanced_ptr, slot_ptr, el2mov * vec->element_size);
    memcpy(slot_ptr, element, vec->element_size);
    vec->count++;
    return true;
}

void SVector_push(SVector* vec, void* element){
    SVector_insert(vec, element, vec->count);
}

//1, 2, 3, 4, 5, _
bool SVector_remove(SVector* vec, size_t idx, void* removed_el){
    if (idx >= vec->count){
        return false;
    }

    void* slot_ptr = ((char*)vec->data) + (idx * vec->element_size);
    if (removed_el){
        memcpy(removed_el, slot_ptr, vec->element_size);
    }

    if (idx == vec->count - 1){
        vec->count--;
        return true;
    }

    size_t el2mov = vec->count - 1 - idx;
    void* advanced_ptr = ((char*)slot_ptr) + (1 * vec->element_size);
    memmove(slot_ptr, advanced_ptr, el2mov * vec->element_size);
    vec->count--;
    return true;
}

bool SVector_pop(SVector* vec, void* popped_el){
    return SVector_remove(vec, vec->count - 1, popped_el);
}
