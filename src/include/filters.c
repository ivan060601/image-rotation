#include <stdint.h>
#include <stddef.h>
#include <malloc.h>
#include "filters.h"

struct matrix
{
    int8_t a1, a2, a3, a4, a5, a6, a7, a8, a9;
    
};

struct image imgcpy(struct image const* image){
    struct image new_image = {
        .height = image->width,
        .width = image->height,
        .data = malloc(sizeof(struct pixel)*image->height*image->width)
    };
    for (size_t i = 0; i < image->height*image->width; i++)
    {
        new_image.data[i] = image->data[i];
    }
    return new_image;
}



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

void inverse(struct image const* image){
    for (size_t i = 0; i < image->height; i++)
    {
        for (size_t j = 0; j < image->width; j++)
        {
            size_t current = i * image->width + j;
            struct pixel* current_pixel = &(image->data[current]);
            current_pixel->b = 255 - current_pixel->b;
            current_pixel->g = 255 - current_pixel->g;
            current_pixel->r = 255 - current_pixel->r;
        }
        
    }
    
}

void sepia(struct image const* image){
    for (size_t i = 0; i < image->height; i++)
    {
        for (size_t j = 0; j < image->width; j++)
        {
            size_t current = i * image->width + j;
            struct pixel* current_pixel = &(image->data[current]);
            uint8_t curr_r = current_pixel->r;
            uint8_t curr_g = current_pixel->g;
            uint8_t curr_b = current_pixel->b;
            current_pixel->b = curr_r * 0.272 + curr_g * 0.534 + curr_b * 0.131;
            current_pixel->g = curr_r * 0.349 + curr_g * 0.686 + curr_b * 0.168;
            current_pixel->r = curr_r * 0.393 + curr_g * 0.769 + curr_b * 0.189;
        }
        
    }
    
}
void general_matrix_transform(struct image const* image, struct matrix a){
    struct image new_image = imgcpy(image);
    
    for (size_t i = 1; i < image->height-1; i++)
    {
        for (size_t j = 1; j < image->width-1; j++)
        {
            size_t current = i * image->width + j;

            struct pixel p1 = new_image.data[(i-1) * image->width + j-1];
            struct pixel p2 = new_image.data[(i-1) * image->width + j];
            struct pixel p3 = new_image.data[(i-1) * image->width + j+1];
            struct pixel p4 = new_image.data[(i) * image->width + j-1];
            struct pixel p5 = new_image.data[(i) * image->width + j];
            struct pixel p6 = new_image.data[(i) * image->width + j+1];
            struct pixel p7 = new_image.data[(i+1) * image->width + j-1];
            struct pixel p8 = new_image.data[(i+1) * image->width + j];
            struct pixel p9 = new_image.data[(i+1) * image->width + j+1];

            struct pixel* current_pixel = &(image->data[current]);
            current_pixel->b = (p1.b*a.a1 + p2.b*a.a2 + p3.b*a.a3 + p4.b*a.a4 + p5.b*a.a5 + p6.b*a.a6 + p7.b*a.a7 + p8.b*a.a8 + p9.b*a.a9);
            current_pixel->g = (p1.g*a.a1 + p2.g*a.a2 + p3.g*a.a3 + p4.g*a.a4 + p5.g*a.a5 + p6.g*a.a6 + p7.g*a.a7 + p8.g*a.a8 + p9.g*a.a9);
            current_pixel->r = (p1.r*a.a1 + p2.r*a.a2 + p3.r*a.a3 + p4.r*a.a4 + p5.r*a.a5 + p6.r*a.a6 + p7.r*a.a7 + p8.r*a.a8 + p9.r*a.a9);
        }
        
    }
}

void laplassian(const struct image *image){
    struct matrix a = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    general_matrix_transform(image, a);
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
}