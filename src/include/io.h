#ifndef _IO_H_
#define _IO_H_
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

typedef enum read_status  reader(FILE* file, struct image* image);
typedef enum write_status writer(FILE* file, struct image* image);

struct reader_ext{
    reader* read_func;
    writer* write_func;
    const char* extention;
};

enum supported_extentions{
    START_EXT = -1,
    //Доступные расширения
    BMP = 0,

    END_EXT
};

reader from_bmp;
writer to_bmp;

enum read_status to_image(FILE* f, struct image* image, const char* filename);
enum write_status from_image(FILE* f, struct image* image, const char* filename);


#endif