#include <stddef.h>

#include "sow_std.h"

int main1(){
    char* input_raw = S_file_get_content_by_filename("input.txt");
    char* input = malloc(strlen(input_raw) - S_stripcount(input_raw) + 1);
    S_strip(input_raw, input);
    free(input_raw);
    SVectorStr strbuilder;
    SVectorStr_init(&strbuilder, 2);
    SVectorStr_push(&strbuilder, input);

    size_t d = 1;
    char dstr[20];
    sprintf(dstr, "%ld", d);
    SVectorStr_push(&strbuilder, dstr);
    char* pass = SVectorStr_join(&strbuilder);
    uint8_t hash[16];
    md5String(pass, hash);
    char hexpass[((ARRLEN(hash))*2)+1];
    S_to_hex_format(hash, ARRLEN(hash), hexpass);
    
    while (!S_startswith(hexpass, "00000")){
        free(pass);
        d++;
        sprintf(dstr, "%ld", d);
        SVectorStr_pop(&strbuilder);
        SVectorStr_push(&strbuilder, dstr);
        pass = SVectorStr_join(&strbuilder);
        md5String(pass,hash);
        S_to_hex_format(hash, ARRLEN(hash), hexpass);
        //notify each 1000 iteration just for feedback
        if (d % 1000 == 0){
            printf("%ld\n", d);
            printf("%s\n", pass);
            printf("%s\n", hexpass);
        }
    }

    printf("la password es: %s\n", pass);
    printf("el hash es: %s\n", hexpass);
    printf("el decimal que es la respuesta: %ld\n", d);
    
    free(pass);
    SVectorStr_free(&strbuilder);
    free(input);
    return 0;
}


int main2(){
    char* input_raw = S_file_get_content_by_filename("input.txt");
    char* input = malloc(strlen(input_raw) - S_stripcount(input_raw) + 1);
    S_strip(input_raw, input);
    free(input_raw);
    SVectorStr strbuilder;
    SVectorStr_init(&strbuilder, 2);
    SVectorStr_push(&strbuilder, input);

    size_t d = 1;
    char dstr[20];
    sprintf(dstr, "%ld", d);
    SVectorStr_push(&strbuilder, dstr);
    char* pass = SVectorStr_join(&strbuilder);
    uint8_t hash[16];
    md5String(pass, hash);
    char hexpass[((ARRLEN(hash))*2)+1];
    S_to_hex_format(hash, ARRLEN(hash), hexpass);
    
    while (!S_startswith(hexpass, "000000")){
        free(pass);
        d++;
        sprintf(dstr, "%ld", d);
        SVectorStr_pop(&strbuilder);
        SVectorStr_push(&strbuilder, dstr);
        pass = SVectorStr_join(&strbuilder);
        md5String(pass,hash);
        S_to_hex_format(hash, ARRLEN(hash), hexpass);
        //notify each 1000 iteration just for feedback
        if (d % 1000 == 0){
            printf("%ld\n", d);
            printf("%s\n", pass);
            printf("%s\n", hexpass);
        }
    }

    printf("la password es: %s\n", pass);
    printf("el hash es: %s\n", hexpass);
    printf("el decimal que es la respuesta: %ld\n", d);
    
    free(pass);
    SVectorStr_free(&strbuilder);
    free(input);
    return 0;
}

int main(void) {
    main1();
    printf("-----------------------------------------\n");
    main2();
    return 0;
}
