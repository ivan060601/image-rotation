#include <malloc.h>
#include "image_structure.h"

void image_free(struct image* image){    
    free(image->data);
    free(image); 
}