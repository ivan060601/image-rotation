#include "image_structure.h"
#include <malloc.h>

void pixel_free(struct pixel* p){
    printf("ooo\n");
    free(&(p->b));
    free(&(p->g));
    free(&(p->r));
    free(p);
}

void image_free(struct image* image){
    for (size_t i = 0; i < image->height*image->width; i++)
    {
        pixel_free(&(image->data[i]));
    }
    
    //free(image);    
}