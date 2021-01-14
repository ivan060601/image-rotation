#include <malloc.h>
#include "image_structure.h"

void pixel_free(struct pixel* p){
    free(p);
}

void image_free(struct image* image){    
    pixel_free(image->data);
    free(image); 
}