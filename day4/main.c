#include <stddef.h>

#include "sow_std.h"

int main1(){
    char* input = S_file_get_content_by_filename("input.txt");
    SVectorStr strbuilder;
    SVectorStr_init(&strbuilder, 2);
    SVectorStr_push(&strbuilder, input);

    size_t d = 1;
    char dstr[100];
    sprintf(dstr, "%ld\0", d);
    SVectorStr_push(&strbuilder, dstr);
    char* pass = SVectorStr_join(&strbuilder);
    char hash[16];
    md5String(pass, hash);
    char* hexpass = S_to_hex_format(hash, 16*2+1);
    
    while (!S_startswith(hexpass, "00000")){
        free(pass);
        free(hexpass);
        d++;
        sprintf(dstr, "%ld\0", d);
        SVectorStr_pop(&strbuilder);
        SVectorStr_push(&strbuilder, dstr);
        pass = SVectorStr_join(&strbuilder);
        md5String(pass,hash);
        hexpass = S_to_hex_format(hash, 16*2+1);
        if (d % 1000 == 0){
            printf("%ld\n", d);
            printf("%s\n", pass);
            printf("%s\n", hexpass);
        }
    }

    printf("la password es: %s\n", pass);
    printf("el decimal que es la respuesta: %ld\n", d);
    
    free(pass);
    SVectorStr_free(&strbuilder);
    free(input);
    return 0;
}

int main(void) {
    main1();
    return 0;
}
