#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include "io.h"

static bool read_header( FILE* f, struct bmp_header* header ) {
    return fread( header, sizeof( struct bmp_header ), 1, f );
}

enum read_status from_bmp(FILE* file, struct image* image){
    //Проверяем заголовок файла
    if (file == NULL)
        return READ_ERROR;
    struct bmp_header header = {0};
    if (!read_header(file, &header))
        return READ_INVALID_BITS;
    if (header.bfType != 19778)
        return READ_INVALID_SIGNATURE;
    if(header.bfReserved != 0 || header.biCompression !=0 || header.biPlanes != 1 || header.biSize != 40 || header.biBitCount != 24)
        return READ_INVALID_HEADER;

    uint8_t* data = malloc(header.biSizeImage);

    //Поставили указатель после заголовка 
    fseek(file, header.bOffBits, SEEK_SET);
    //Считываем содержимое
    fread(data, 1, header.biSizeImage, file);

    image->data = malloc(header.biWidth*header.biHeight*sizeof(struct pixel));

    uint8_t padding = header.biWidth % 4;
    
    for (size_t i = 0; i < header.biHeight; i++)
    {
        for (size_t j = 0; j < header.biWidth; j++)
        {
            size_t current = i * header.biWidth + j;
            size_t delta = sizeof(struct pixel) * current + padding * i;
            image->data[current] = *(struct pixel*)(data + delta);
        }
    }

    free(data);
    return READ_OK;
}

enum write_status  to_bmp(FILE* file, struct image* image){

    return WRITE_OK;
}

struct image* image_malloc(){
    return (struct image*)malloc(sizeof(struct image));
}
