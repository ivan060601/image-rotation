#include <stdint.h>
#include <stddef.h>
#include <malloc.h>
#include "filters.h"

void grayscale_filter(struct image const* image){
    for (size_t i = 0; i < image->height; i++)
    {
        for (size_t j = 0; j < image->width; j++)
        {
            size_t current = i * image->width + j;
            struct pixel* current_pixel = &(image->data[current]);
            uint8_t new_colour = (uint8_t)(current_pixel->b*0.11 + current_pixel->g*0.59 + current_pixel->r*0.30);
            current_pixel->b = new_colour;
            current_pixel->g = new_colour;
            current_pixel->r = new_colour;
        }
        
    }
    
}

struct image rotate_and_create_new_image(struct image const* image){
    struct image new_image = {
        .height = image->width,
        .width = image->height,
        .data = malloc(sizeof(struct pixel)*image->height*image->width)
    };

    for (size_t i = 0; i < image->height; i++)
    {
        for (size_t j = 0; j < image->width; j++)
        {
            new_image.data[i + image->height*(image->width-j-1)]=image->data[i*image->width+j];
        }
        
    }
    
    return new_image;
}

void rotate_existing_image(struct image* const image){
    struct image new_image = rotate_and_create_new_image(image);

    image->height = new_image.height;
    image->width = new_image.width;

    for (size_t i = 0; i < image->height*image->width; i++)
    {
        image->data[i] = new_image.data[i];
    }
    //image_free(&new_image);    
}