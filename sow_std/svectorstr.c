#include "svectorstr.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "svector.h"

#define GROW_FACTOR 2


//FORWARD DECLARATIONS
static void SVectorStr_ensure_capacity(SVectorStr* vec);


static void SVectorStr_ensure_capacity(SVectorStr* vec){
    if (vec->count < vec->capacity){
        return;
    }

    SVectorStr_recapacity(vec, vec->capacity * GROW_FACTOR);
}


void SVectorStr_init(SVectorStr* vec, size_t cap){
    vec->count = 0;
    vec->capacity = cap;
    vec->data = malloc(sizeof(char**) * cap);
}

void SVectorStr_free(SVectorStr* vec){
    vec->count = 0;
    vec->capacity = 0;
    for (size_t i=0; i<vec->count; ++i){
        char* c = vec->data[i];
        free(c);
    }
    free(vec->data);
    vec->data = NULL;
}

bool SVectorStr_recapacity(SVectorStr* vec, size_t new_cap){
    if (vec->count > new_cap){
        return false;
    }

    void* new_data = realloc(vec->data, sizeof(char**) * new_cap);
    vec->capacity = new_cap;
    vec->data = new_data;
    return true;
}


bool SVectorStr_insert(SVectorStr* vec, const char* element, size_t idx){
    if (idx > vec->count){
        return false;
    }

    SVectorStr_ensure_capacity(vec);

    char** slot_ptr = vec->data + idx;
    size_t strl = strlen(element);
    //if it is the last element
    if (idx == vec->count){
        *slot_ptr = malloc((strl * sizeof(char)) + 1);
        strcpy(*slot_ptr, element);
        (*slot_ptr)[strl] = '\0';
        vec->count++;
        return true;
    }
    
    size_t el2mov = vec->count - idx;
    char** advanced_ptr = slot_ptr + 1;
    memmove(advanced_ptr, slot_ptr, el2mov * sizeof(char**));
    *slot_ptr = malloc((strl * sizeof(char)) + 1);
    strcpy(*slot_ptr, element);
    (*slot_ptr)[strl] = '\0';
    vec->count++;
    return true;
}

void SVectorStr_push(SVectorStr* vec, const char* element){
    SVectorStr_insert(vec, element, vec->count);
}

bool SVectorStr_remove(SVectorStr* vec, size_t idx){
    if (idx >= vec->count){
        return false;
    }

    char** slot_ptr = vec->data + idx;
    free(*slot_ptr);
    //if it's last element to remove just simulate remove but let the object there "optimization baby"
    //anyway the next push will ovewrite that object.
    if (idx == vec->count - 1){
        vec->count--;
        return true;
    }

    size_t el2mov = vec->count - 1 - idx;
    char** advanced_ptr = slot_ptr + 1;
    memmove(slot_ptr, advanced_ptr, el2mov * sizeof(char**));
    vec->count--;
    return true;
}

bool SVectorStr_pop(SVectorStr* vec){
    return SVectorStr_remove(vec, vec->count - 1);
}

//Join all strings in one. Note you have to free that returned str.
//TODO: could it be better receive the buffer and fill it?
char* SVectorStr_join(SVectorStr* vec){
    size_t totallen = 0;
    SVector strlens;
    SVector_init(&strlens, sizeof(size_t), vec->count);

    for(size_t i = 0; i<vec->count;++i){
        size_t* len_ptr = ((size_t*)strlens.data) + i;
        char* c = vec->data[i];
        size_t clen = strlen(c);
        *len_ptr = clen;
        totallen += clen;
    }

    char* joined_str = (char*)malloc(totallen + 1);

    size_t joinidx = 0;
    for(size_t i = 0; i<vec->count;++i){
        char* c = vec->data[i];
        size_t l = *(((size_t*)strlens.data) + i);
        char* dest = joined_str + joinidx;
        joinidx += l;
        memmove(dest, c, l);
    }
    joined_str[totallen] = '\0';

    SVector_free(&strlens);
    return joined_str;
}
