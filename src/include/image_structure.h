#include <stdint.h>
#ifndef _IMAGE_STRUCT_
#define _IMAGE_STRUCT_

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

#endif