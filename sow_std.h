#ifndef __SOW_STD_H__
#define __SOW_STD_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

typedef struct VectorStr VectorStr;
void sow_vectorStr_push(VectorStr* v, const char* value);

char* sow_get_input(){
    FILE* f = fopen("input.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fc = ftell(f);

    char* buffer = (char*) malloc(fc + 1);
    rewind(f);

    fread(buffer, 1, fc + 1, f);
    return buffer;
}

void sow_split_by_delim_char(VectorStr* v, const char* input, char delim){
    size_t count = strlen(input);
    if (count <= 0){
        return;
    }

    size_t cend = 0;
    const char* start = input;
    for(size_t i=0; i<count;++i){
        char c = input[i];
        const char* cend = input + i; 
        if (c == delim){
            size_t len = cend - start;
            char* copy = malloc(len + 1);
            if (len > 0){
                memcpy(copy, start, len);
            }
            copy[len] = '\0';
            sow_vectorStr_push(v, copy);
            free(copy);

            start = cend + 1;
        }
    }
    char* copy = malloc(strlen(start) + 1);
    strcpy(copy, start);
    sow_vectorStr_push(v, copy);
}

void sow_split_by_lines(VectorStr* v, const char* input){
    size_t count = strlen(input);
    if (count <= 0){
        return;
    }

    size_t cend = 0;
    const char* start = input;
    for(size_t i=0; i<count;++i){
        char c = input[i];
        const char* cend = input + i; 
        if (c == '\n'){
            size_t len = cend - start;
            char* copy = malloc(len + 1);
            if (len > 0){
                memcpy(copy, start, len);
            }
            copy[len] = '\0';
            sow_vectorStr_push(v, copy);
            free(copy);

            start = cend + 1;
        }
    }
    char* copy = malloc(strlen(start) + 1);
    strcpy(copy, start);
    sow_vectorStr_push(v, copy);
}

int64_t sow_min(int64_t* ns, size_t count){
    int64_t m = INT64_MAX;
    for(size_t i = 0; i<count; i++){
        int64_t cn = ns[i];
        if (cn < m){
            m = cn;
        }
    }
    return m;
}

int64_t sow_max(int64_t* ns, size_t count){
    int64_t m = INT64_MIN;
    for(size_t i = 0; i<count; i++){
        int64_t cn = ns[i];
        if (cn > m){
            m = cn;
        }
    }
    return m;
}
 

//-----VECTOR_STRINGS-------
typedef struct VectorStr {
    char** data;
    size_t count;
    size_t capacity;
} VectorStr;

void sow_init_vector_str(VectorStr* v, size_t cap){
    v->data = (char**) malloc(sizeof(char*)*cap);
    v->capacity = cap;
    v->count = 0;
}

void sow_vectorStr_push(VectorStr* v, const char* value){
    if (v->count >= v->capacity){
        v->data = realloc(v->data, sizeof(char*) * v->capacity * 2);
        v->capacity *= 2;
    }

    v->data[v->count] = (char*) malloc(strlen(value) + 1);
    strcpy(v->data[v->count], value);
    v->count++;
}


#endif //__SOW_STD_H__
