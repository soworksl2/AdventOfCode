#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "svectorstr.h"


int main(void){
    SVectorStr vec;
    SVectorStr_init(&vec, 2);

    SVectorStr_push(&vec, "Hola mundo");
    SVectorStr_push(&vec, "Como se encuentran?");
    SVectorStr_push(&vec, "Porque yo muy mal");

    SVectorStr_insert(&vec, "Yo me Amo A MI BB\n    --------------------------------", 0);
    SVectorStr_remove(&vec, 3);
    SVectorStr_push(&vec, "Porque yo muy Bien");
    SVectorStr_push(&vec, "kakaka");
    SVectorStr_push(&vec, "kakariko");
    SVectorStr_remove(&vec, vec.count - 2);
    

    printf("vector count: %ld\n", vec.count);
    printf("vector cap: %ld\n", vec.capacity);

    printf("------------------------------------------\n");
    for(size_t i=0; i<vec.count; ++i){
        char* c = vec.data[i];
        printf("    [%ld] = %s\n", i, c);
    }

    printf("------------------------------------------\n");
    printf("------------------------------------------\n");

    char* allstr = SVectorStr_join(&vec);
    printf("%s\n", allstr);

    SVectorStr_free(&vec);
    free(allstr);
    return 0;
}
