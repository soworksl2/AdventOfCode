#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

char* get_input(){
    FILE* f = fopen("input.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fc = ftell(f);

    char* buffer = (char*) malloc(fc + 1);
    rewind(f);

    fread(buffer, 1, fc + 1, f);
    return buffer;
}

void solve(char* input){
    size_t count = strlen(input) - 1;
    int32_t position = 0;
    for (size_t i=0; i<count;++i){
        char cc = input[i];
        if (cc == '('){
            position++;
        }else if(cc == ')'){
            position--;
        }else{
            assert(false);
        }
    }
    printf("La posicion es: %d\n", position);
}

void solve2(char* input){
    size_t count = strlen(input) - 1;
    int32_t position = 0;
    int32_t cursor = 0;
    for (size_t i=0; i<count;++i){
        char cc = input[i];
        cursor++;
        if (cc == '('){
            position++;
        }else if(cc == ')'){
            position--;
        }else{
            assert(false);
        }
        if (position <= -1){
            printf("La posicion del caracter es: %d\n", cursor);
            return;
        }
    }
}

int main(){
    char* input = get_input();

    solve(input);
    solve2(input);

    free(input);
    return 0;
}
