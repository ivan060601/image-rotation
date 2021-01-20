#include <stdint.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "filters.h"

struct matrix
{
    int8_t coeff[9];
};

struct image imgcpy(struct image const* image){
    struct image new_image = {
        .height = image->width,
        .width = image->height,
        .data = malloc(sizeof(struct pixel)*image->height*image->width)
    };

    memcpy(new_image.data, image->data, sizeof(struct pixel)*image->height*image->width);
    return new_image;
}

void grayscale_filter(struct image const* image){
    for (uint64_t i = 0; i < image->height; i++)
    {
        for (uint64_t j = 0; j < image->width; j++)
        {
            const uint64_t current = i * image->width + j;
            struct pixel* current_pixel = &(image->data[current]);
            const uint8_t new_colour = (uint8_t)(current_pixel->b*0.11 + current_pixel->g*0.59 + current_pixel->r*0.30);
            current_pixel->b = new_colour;
            current_pixel->g = new_colour;
            current_pixel->r = new_colour;
        }
        
    }
    
}

void inverse(struct image const* image){
    for (uint64_t i = 0; i < image->height; i++)
    {
        for (uint64_t j = 0; j < image->width; j++)
        {
            const uint64_t current = i * image->width + j;
            struct pixel* current_pixel = &(image->data[current]);
            current_pixel->b = 255 - current_pixel->b;
            current_pixel->g = 255 - current_pixel->g;
            current_pixel->r = 255 - current_pixel->r;
        }
        
    }
    
}

void sepia(struct image const* image){
    for (uint64_t i = 0; i < image->height; i++)
    {
        for (uint64_t j = 0; j < image->width; j++)
        {
            const uint64_t current = i * image->width + j;
            struct pixel* current_pixel = &(image->data[current]);
            const uint8_t curr_r = current_pixel->r;
            const uint8_t curr_g = current_pixel->g;
            const uint8_t curr_b = current_pixel->b;
            current_pixel->b = curr_r * 0.272 + curr_g * 0.534 + curr_b * 0.131;
            current_pixel->g = curr_r * 0.349 + curr_g * 0.686 + curr_b * 0.168;
            current_pixel->r = curr_r * 0.393 + curr_g * 0.769 + curr_b * 0.189;
        }
        
    }
    
}
void general_matrix_transform(struct image const* image, struct matrix a){
    struct image new_image = imgcpy(image);
    
    for (uint64_t i = 1; i < image->height-1; i++)
    {
        for (uint64_t j = 1; j < image->width-1; j++)
        {
            const uint64_t current = i * image->width + j;

            //Это, наверное, тоже можно впихнуть в массив, как и struct matrix, но места вроде также займет
            const struct pixel p1 = new_image.data[(i-1) * image->width + j-1];
            const struct pixel p2 = new_image.data[(i-1) * image->width + j];
            const struct pixel p3 = new_image.data[(i-1) * image->width + j+1];
            const struct pixel p4 = new_image.data[(i) * image->width + j-1];
            const struct pixel p5 = new_image.data[(i) * image->width + j];
            const struct pixel p6 = new_image.data[(i) * image->width + j+1];
            const struct pixel p7 = new_image.data[(i+1) * image->width + j-1];
            const struct pixel p8 = new_image.data[(i+1) * image->width + j];
            const struct pixel p9 = new_image.data[(i+1) * image->width + j+1];

            struct pixel* current_pixel = &(image->data[current]);
            current_pixel->b = (p1.b*a.coeff[0] + p2.b*a.coeff[1] + p3.b*a.coeff[2] + p4.b*a.coeff[3] + p5.b*a.coeff[4] + p6.b*a.coeff[5] + p7.b*a.coeff[6] + p8.b*a.coeff[7] + p9.b*a.coeff[8]);
            current_pixel->g = (p1.g*a.coeff[0] + p2.g*a.coeff[1] + p3.g*a.coeff[2] + p4.g*a.coeff[3] + p5.g*a.coeff[4] + p6.g*a.coeff[5] + p7.g*a.coeff[6] + p8.g*a.coeff[7] + p9.g*a.coeff[8]);
            current_pixel->r = (p1.r*a.coeff[0] + p2.r*a.coeff[1] + p3.r*a.coeff[2] + p4.r*a.coeff[3] + p5.r*a.coeff[4] + p6.r*a.coeff[5] + p7.r*a.coeff[6] + p8.r*a.coeff[7] + p9.r*a.coeff[8]);
        }
        
    }
}

void laplassian(const struct image *image){
    const struct matrix a = (struct matrix){.coeff =  {0, -1, 0, -1, 4, -1, 0, -1, 0}};
    general_matrix_transform(image, a);
}

struct image rotate(struct image const* image){
    struct image new_image = {
        .height = image->width,
        .width = image->height,
        .data = malloc(sizeof(struct pixel)*image->height*image->width)
    };

    for (uint64_t i = 0; i < image->height; i++)
    {
        for (uint64_t j = 0; j < image->width; j++)
        {
            new_image.data[i + image->height*(image->width-j-1)]=image->data[i*image->width+j];
        }
        
    }
    
    return new_image;
}

void rotate_existing_image(struct image* const image){
    const struct image new_image = rotate(image);

    image->height = new_image.height;
    image->width = new_image.width;

    for (uint64_t i = 0; i < image->height*image->width; i++)
    {
        image->data[i] = new_image.data[i];
    }
}