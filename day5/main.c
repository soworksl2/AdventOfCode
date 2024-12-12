#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<stdbool.h>
#include<string.h>

#include "sow_std.h"

size_t count_vowels(const char* str){
    size_t l = strlen(str);
    size_t vowels=0;
    for (size_t i=0; i<l; ++i){
        char c=str[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            vowels++;
        }
    }
    return vowels;
}

bool has_repeated(const char* str){
    char before = 0;
    size_t l = strlen(str);

    for(size_t i=0; i<l; ++i){
        char c = str[i];
        if(before == c){
            return true;
        }
        before=c;
    }
    return false;
}

bool has_pair_repeat(const char* str){
    size_t l = strlen(str);

    char pair[3];
    pair[2] = '\0';
    const char* str_offset;
    for (size_t i=0; i<l-3;++i){
        memcpy(pair, str+i, 2);
        str_offset = str+i+2;

        if (strstr(str_offset, pair)){
            printf("    %s\n", pair);
            return true;
        }
    }
    return false;
}

bool has_pattern_with_obstacle(const char* str){
    size_t l = strlen(str);
    for (size_t i=0; i<l-2; ++i){
        char c1 = str[i];
        char obstacle = str[i+1];
        char c2 = str[i+2];

        if (c1 == c2){
            printf("    %c%c%c\n", c1, obstacle, c2);
            return true;
        }
    }
    return false;
}

bool is_valid_string2(const char* str){
    return has_pair_repeat(str) && has_pattern_with_obstacle(str);
}

bool is_valid_string(const char* str){
    bool contains_ab = (strstr(str, "ab") != NULL);
    bool contains_cd = (strstr(str, "cd") != NULL);
    bool contains_pq = (strstr(str, "pq") != NULL);
    bool contains_xy = (strstr(str, "xy") != NULL);

    bool contains_invalid_pattern = contains_ab || contains_cd || contains_pq || contains_xy;

    size_t vowels = count_vowels(str);
    bool contains_repeated = has_repeated(str);
    return (vowels >= 3) && contains_repeated && !contains_invalid_pattern;
}

void solve1(){
    char* input = S_file_get_content_by_filename("input.txt");
    SVectorStr lines;
    SVectorStr_init(&lines, 10);
    S_split(input, "\n", &lines);
    SVectorStr_pop(&lines); //delete the last empty string
    
    size_t nice_strs=0;
    for(size_t i=0; i<lines.count; ++i){
        char* c=lines.data[i];
        bool is_nice = is_valid_string(c);
        char* nice_txt;

        if (is_nice){
            nice_txt="true";
            nice_strs++;
        }else{
            nice_txt="false";
        }
        printf("%s -> %s\n", c, nice_txt);
    }
    printf("\n");
    printf("the nice strings are: %ld\n", nice_strs);
}

void solve2(){
    char* input = S_file_get_content_by_filename("input.txt");
    SVectorStr lines;
    SVectorStr_init(&lines, 10);
    S_split(input, "\n", &lines);
    SVectorStr_pop(&lines); //delete the last empty string
    
    size_t nice_strs=0;
    for(size_t i=0; i<lines.count; ++i){
        char* c=lines.data[i];
        bool is_nice = is_valid_string2(c);
        char* nice_txt;

        if (is_nice){
            nice_txt="true";
            nice_strs++;
        }else{
            nice_txt="false";
        }
        printf("%s -> %s\n", c, nice_txt);
    }
    printf("\n");
    printf("the nice strings are: %ld\n", nice_strs);
}

int main(){
    solve1();
    printf("-----------------------------------\n");
    solve2();
    return 0;
}
