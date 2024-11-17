#ifndef __SSTR_H__
#define __SSTR_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "svectorstr.h"


//split str by a delim creating a lot of news strings dinamically and saved in vecstr
//vecstr have ownership, so calling SVectorStr_free will free all strs.
void S_split(const char* str, const char* delim, SVectorStr* vecstr);

//like python startswith
bool S_startswith(const char* str, const char* p);

//like python endswith
bool S_endswith(const char* str, const char* p);

//strip the left side of str and save it to buf
//if buf does not have enough space it is undefined behaviour
//tip: you can use S_striplcount to be precise in the buf capacity
void S_stripl(const char* str, char* buf);

//like S_stripl but at the right side
void S_stripr(const char* str, char* buf);

//like S_stripl but at both side. is the same as calling S_stripl and S_stripr consecutively.
//but this function is optimized.
void S_strip(const char* str, char* buf);

//counts how many chars could be eliminated if calling S_stripl
size_t S_striplcount(const char* str);

//the same as S_striplcount but at the right side
size_t S_striprcount(const char* str);

//the same as S_striplcount but at both side.
size_t S_stripcount(const char* str);

//Convert a string interpreted as a buffer of unsigned char to another string as hexadecimal
//buf needs to be (count * 2) + 1 or it is undefined behaviour.
void S_to_hex_format(const uint8_t* bytes, size_t count, char* buf);


#endif //__SSTR_H__
