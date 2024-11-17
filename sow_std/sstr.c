#include "sstr.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>


//FORWARD DECLARATIONS
static const char* S_striplf(const char* str);
static const char* S_striprf(const char* str);


static const char* S_striplf(const char* str){
    const char* startptr = str;
    while (startptr) {
        if(!isspace(*startptr)){
            break;
        }
        startptr++;
    }
    return startptr;
}

static const char* S_striprf(const char* str){
    size_t l = strlen(str);
    const char* endptr = str + l - 1;
    const char* bstart = str - 1;
    while(endptr != bstart){
        if (!isspace(*endptr)){
            break;
        }
        endptr--;
    }
    return endptr;
}


void S_split(const char* str, const char* delim, SVectorStr* vecstr){
    size_t strl = strlen(str);
    size_t deliml = strlen(delim);
    if (strl == 0){
        return;
    }

    if (deliml == 0){
        SVectorStr_push(vecstr, str);
        return;
    }

    const char* csplit = str;
    char* nsplit;
    while(true) {
        nsplit = strstr(csplit, delim);
        
        if(!nsplit){
            SVectorStr_push(vecstr, csplit);
            break;
        }

        size_t clen = nsplit - csplit;
        char* strtmp = malloc(clen + 1);
        memcpy(strtmp, csplit, clen);
        strtmp[clen] = '\0';
        SVectorStr_push(vecstr, strtmp);
        free(strtmp);
        csplit = nsplit + deliml;
    }
} 

bool S_startswith(const char* str, const char* p){
    char* aparition = strstr(str, p);
    return aparition == str;
}

bool S_endswith(const char* str, const char* p){
    size_t pl = strlen(p);
    size_t strl = strlen(str);
    if (pl > strl){
        return false;
    }

    const char* pa = (str + (strl - 1)) - (pl - 1);
    return strcmp(pa, p) == 0;
}

void S_stripl(const char* str, char* buf){
    const char* startptr = S_striplf(str);
    size_t l = strlen(startptr);
    strcpy(buf, startptr);
    buf[l] = '\0';
}

void S_stripr(const char* str, char* buf){
    const char* endptr = S_striprf(str);
    size_t l = endptr - str + 1;
    memcpy(buf, str, l);
    buf[l] = '\0';
}

void S_strip(const char* str, char* buf){
    const char* startptr = S_striplf(str);
    const char* endptr = S_striprf(str);
    int32_t l = endptr - startptr;
    l = (l < 0)? 0 : l + 1;
    memcpy(buf, startptr, l);
    buf[l] = '\0';
}

size_t S_striplcount(const char* str){
    const char* startptr = S_striplf(str);
    return startptr - str;
}

size_t S_striprcount(const char* str){
    const char* endptr = S_striprf(str);
    const size_t strl = strlen(str);
    const char* endfptr = str + strl - 1;
    return endfptr - endptr;
}
size_t S_stripcount(const char* str){
    //TODO: this probably need optimization but I am tired boss :_(
    //I have already like 6 or 7 hours coding and this is not a serious project
    size_t s = S_striplcount(str);
    size_t e = S_striprcount(str);
    return s + e;
}

void S_to_hex_format(const uint8_t* bytes, size_t count, char* buf){
    for (size_t i = 0; i < count; ++i) {
        sprintf(&buf[i * 2], "%02x", bytes[i]);
    }

    buf[count * 2] = '\0';
}
