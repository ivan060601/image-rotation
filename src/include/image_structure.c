#include "image_structure.h"
#include <malloc.h>

void image_malloc(struct image* image){
    image =  (struct image*)malloc(sizeof(struct image));
}
