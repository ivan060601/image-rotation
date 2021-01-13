#ifndef _IO_H_
#define _IO_H_
#include <stdbool.h>
#include "image_structure.h"
#include "bmp.h"


enum read_status  {
    READ_OK = 10,
    READ_ERROR,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    NOT_ENOUGHT_ARGS,
    TOO_MANY_ARGS
};

enum  write_status  {
    WRITE_OK = 20,
    WRITE_ERROR
};

struct image* image_malloc();
bool image_free(struct image * image);

enum read_status from_bmp(FILE* file, struct image* image);
enum write_status  to_bmp(FILE* file, struct image* image);


#endif