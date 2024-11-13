#include "sfile.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


long S_file_get_count_bytes(FILE* f){
    long saved_curpos = ftell(f);
    if(saved_curpos == -1L){
        return -1L;
    }

    fseek(f, 0, SEEK_END);
    long end_curpos = ftell(f);
    fseek(f, saved_curpos, SEEK_SET);
    return end_curpos;
}

size_t S_file_get_content(FILE* f, char* buf){
    long saved_curpos = ftell(f);

    if (saved_curpos == -1L){
        return 0;
    }

    fseek(f, 0, SEEK_SET);
    long total_bytes = S_file_get_count_bytes(f);
    long br = fread(buf, sizeof(char), total_bytes, f);
    
    fseek(f, saved_curpos, SEEK_SET);
    return br;
}

char* S_file_get_content_by_filename(const char* filename){
    FILE* f = fopen(filename, "rb");

    if (!f){
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    size_t bufl = sz + 1;
    char* buf = (char*)malloc(bufl);
    rewind(f);
    fread(buf, sizeof(char), sz, f);
    fclose(f);
    return buf;
}
