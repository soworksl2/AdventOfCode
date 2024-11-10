#include <stdio.h>
#include <stddef.h>

#include "smath.h"


int main(void){
    int x;
    int l[] = {1,2,3,4,5,6,7,8,9,10};
    MAX(int, l, ARRLEN(l), x);
   
    printf("max: %d\n", x);
    printf("-------------------------------\n");

    int m;
    int lm[] = {9, 5, 3, -2, 100};
    MIN(int, lm, ARRLEN(lm), m);

    printf("min: %d\n", m);

    int sum;
    SUM(int, l, ARRLEN(l), sum);

    printf("suma: %d", sum);
    
    return 0;
}
