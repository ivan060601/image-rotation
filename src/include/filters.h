#ifndef _FILTERS_H_
#define _FILTERS_H_
#include "image_structure.h"
typedef void filter(struct image const* image);

filter grayscale_filter;
void rotate_existing_image(struct image* const image);

struct image rotate_and_create_new_image(struct image const* image);

#endif