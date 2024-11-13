#ifndef __SFILE_H__
#define __SFILE_H__

#include <stdio.h>
#include <stdbool.h>


//get the total count of bytes in the FILE f
long S_file_get_count_bytes(FILE* f);

//writes the whole content of the FILE f to buf. no matters the cursor position.
//the position is set back when read.
size_t S_file_get_content(FILE* f, char* buf);

//read the whole content of file specified by filename
char* S_file_get_content_by_filename(const char* filename);


#endif //__SFILE_H__
