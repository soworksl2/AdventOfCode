#include <stdio.h>
#include <stdlib.h>

#include "../sow_std.h"

typedef struct{
    int32_t l;
    int32_t w;
    int32_t h;
} Dimension;

typedef struct {
    Dimension* data;
    size_t count;
    size_t capacity;
} VectorDimension;

int32_t dimension_get_total_paper_to_buy(Dimension d){
    int64_t front = d.w * d.h;
    int64_t side = d.l * d.h;
    int64_t head = d.w * d.l;

    int64_t arr[3] = {front, side, head};
    int64_t min_face = sow_min(arr, 3);
    return (front*2) + (side*2) + (head*2) + min_face;
}

int32_t ribbon_and_bow_how_many(Dimension d){
    int32_t bow = d.l * d.w * d.h;

    int64_t front = d.h+d.h+d.w+d.w;
    int64_t side = d.h+d.h+d.l+d.l;
    int64_t head = d.l+d.l+d.w+d.w;

    int64_t arr[3] = {front, side, head};
    int64_t min_face = sow_min(arr, 3);
    return bow + min_face;
}

void init_vector_dimensions(VectorDimension* v, size_t cap){
    v->data = (Dimension*) malloc(sizeof(Dimension)*cap);
    v->capacity = cap;
    v->count = 0;
}

void vector_dimensions_push(VectorDimension* v, Dimension d){
    if (v->count >= v->capacity){
        v->data = realloc(v->data, sizeof(Dimension) * v->capacity * 2);
        v->capacity *= 2;
    }

    v->data[v->count] = d;
    v->count++;
}

void parse_dimension(Dimension* d, const char* str){
    VectorStr components; 
    sow_init_vector_str(&components, 2);
    sow_split_by_delim_char(&components, str, 'x');

    char* l = components.data[0];
    char* w = components.data[1];
    char* h = components.data[2];
    
    int32_t li = atoi(l);
    int32_t wi = atoi(w);
    int32_t hi = atoi(h);

    d->l = li;
    d->w = wi;
    d->h = hi;
}

void parse_input_to_dimensions(VectorDimension* v, const char* input){
    VectorStr strs;
    sow_init_vector_str(&strs, 2);
    sow_split_by_lines(&strs, input);

    Dimension d;
    for (size_t i=0; i<strs.count; ++i){
        if (strlen(strs.data[i]) <= 0){
            continue;
        }
        char* str = strs.data[i];
        parse_dimension(&d, str);
        vector_dimensions_push(v, d);
    }
}

int main(){
    char* input = sow_get_input();
    VectorDimension dims;
    init_vector_dimensions(&dims, 2);
    parse_input_to_dimensions(&dims, input);

    int32_t total = 0;
    int32_t total_ribbon = 0;
    for(size_t i = 0; i<dims.count; ++i){
        Dimension c = dims.data[i];
        int32_t cs = dimension_get_total_paper_to_buy(c);
        int32_t ctribbon = ribbon_and_bow_how_many(c);
        total += cs;
        total_ribbon += ctribbon;
        printf("(%dx%dx%d) -> %d\n", c.l, c.w, c.h, cs);
    }

    printf("Total: %d", total);
    printf("Total of ribbon: %d", total_ribbon);

    return 0;
}
