#include <stdint.h>
#include <stdbool.h>
#ifndef _IMAGE_STRUCT_
#define _IMAGE_STRUCT_

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

void image_malloc(struct image* image);
bool image_free(struct image * image);

#endif