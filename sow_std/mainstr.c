#include "sstr.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "svectorstr.h"

int main(void){
    
    const char* str = "hola mundo\ncomo estan\nesto es un texto\nen multiples lineas";
    SVectorStr strsplitted;
    SVectorStr_init(&strsplitted, 2);

    S_split(str, "\n", &strsplitted);

    
    printf("count: %ld\n", strsplitted.count);

    for (size_t i=0; i < strsplitted.count; ++i){
        const char* c = strsplitted.data[i];
        printf("    [%ld] = %s\n", i, c);
    }

    
    SVectorStr_free(&strsplitted);

    printf("empieza con patron?: %d\n", S_startswith(str, "papa"));
    printf("termina con patron?: %d\n", S_endswith(str, "kakariko"));

    char buf[100];
    size_t f = S_striplcount("    hola mundo    ");
    S_stripl("    hola mundo    ", buf);

    printf("removed: %ld\n'%s'\n", f, buf);

    f = S_striprcount("    hola mundo    ");
    S_stripr("    hola mundo    ", buf);
    printf("removed: %ld\n'%s'\n", f, buf);

    f = S_stripcount("    hola mundo    ");
    S_strip("    hola mundo    ", buf);
    printf("removed: %ld\n'%s'\n", f, buf);
    return 0;
}
