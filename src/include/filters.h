#ifndef _FILTERS_H_
#define _FILTERS_H_
#include "image_structure.h"

typedef void filter(struct image const* image);

enum available_filters{
    START_FIL = -1,
    //Доступные фильтры
    ROTATE_SAVE = 0,
    ROTATE_EX,
    GRAYSCALE,
    INVERSE,
    SEPIA,
    LAPLASSIAN,

    END_FIL
};

filter grayscale_filter;
filter laplassian;
filter inverse;
filter sepia;

void rotate_existing_image(struct image* const image);

struct image rotate_and_create_new_image(struct image const* image);

#endif