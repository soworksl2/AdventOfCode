#include <stdio.h>
#include <stddef.h>

#include "svector.h"


int main(void){
    SVector vecint;
    SVector_init(&vecint, sizeof(int), 2);

    SVECTOR_PUSH(int, &vecint, 1);
    SVECTOR_PUSH(int, &vecint, 2);
    SVECTOR_PUSH(int, &vecint, 3);
    SVECTOR_PUSH(int, &vecint, 4);
    SVECTOR_PUSH(int, &vecint, 5);
    SVECTOR_PUSH(int, &vecint, 6);
    SVECTOR_PUSH(int, &vecint, 7);
    SVECTOR_PUSH(int, &vecint, 8);

    SVECTOR_INSERT(int, &vecint, 100, 0);

    int p1,p2;

    SVector_remove(&vecint, 6, &p1);
    SVector_pop(&vecint, &p2);

    printf("vector count: %ld\n", vecint.count);
    printf("vector cap: %ld\n", vecint.capacity);
    printf("vector element_size: %ld\n", vecint.element_size);

    printf("------------------------------------------\n");
    for(size_t i=0; i<vecint.count; ++i){
        int c = ((int*)vecint.data)[i];
        printf("    [%ld] = %d\n", i, c);
    }
    printf("------------------------------------------\n");

    printf("p1 = %d\n", p1);
    printf("p2 = %d\n", p2);

    SVector_free(&vecint);
    return 0;
}
