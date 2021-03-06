#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
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
    if (header.bfType != BMP_SIGNATURE)
        return READ_INVALID_SIGNATURE;
    if(header.bfReserved != 0 || header.biCompression !=0 || header.biPlanes != 1 || header.biSize != 40 || header.biBitCount != 24 || header.biSizeImage == 0)
        return READ_INVALID_HEADER;

    uint8_t* data = malloc(header.biSizeImage);

    //Поставили указатель после заголовка 
    fseek(file, header.bOffBits, SEEK_SET);
    //Считываем содержимое
    fread(data, 1, header.biSizeImage, file);

    image->data = malloc(header.biWidth*header.biHeight*sizeof(struct pixel));
    image->width = header.biWidth;
    image->height = header.biHeight;
    
    const uint64_t padding = header.biWidth % 4;
    
    for (uint64_t i = 0; i < header.biHeight; i++)
    {
        for (uint64_t j = 0; j < header.biWidth; j++)
        {
            const uint64_t current = i * header.biWidth + j;
            const uint64_t delta = sizeof(struct pixel) * current + padding * i;
            image->data[current] = *(struct pixel*)(data + delta);
        }
    }

    free(data);
    return READ_OK;
}

struct bmp_header create_header(struct image* image){
    struct bmp_header new_header = {
        .bfType = BMP_SIGNATURE,
        .bfileSize = sizeof(struct bmp_header) + image->height * (image->width * sizeof(struct pixel*) + image->width % 4),
        .bfReserved = 0,
        .bOffBits = sizeof(struct bmp_header),
        .biSize = 40,
        .biWidth = image->width,
        .biHeight = image->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = image->height * (image->width * sizeof(struct pixel) + image->width % 4 ),
        .biXPelsPerMeter = 0, //Я так и не понял, как вычисляется это число, ибо постоянно мое число выходит больше, чем у оригинала
        .biYPelsPerMeter = 0, //Аналогично
        .biClrUsed = 0,
        .biClrImportant = 0
    };
    return new_header;
}

enum write_status to_bmp(FILE* file, struct image* image){

    //Создадим заголовок будущего файла
    const struct bmp_header new_header = create_header(image);

    //Пишем заголовок
    if (!fwrite(&new_header, 1, sizeof(struct bmp_header), file))
        return WRITE_ERROR;

    const uint8_t padding = image->width % 4;
    
    //Пишем данные
    if (!fwrite(image->data, 1, (image->width + (padding)) * image->height * sizeof(struct pixel), file))
        return WRITE_ERROR;

    return WRITE_OK;
}

struct reader_ext extentions[] =
{
    [BMP] = {from_bmp, to_bmp, "bmp"}
};

int get_filename_index(const char* filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) 
        return -1;

    for (int i = START_EXT+1; i < END_EXT; i++)
    {
        if(strcmp(extentions[i].extention, (dot+1)) == 0){
            return i;
        }
    }
    return -1;
}

enum read_status to_image(FILE* f, struct image* image, const char* filename){
    const enum supported_extentions e = (enum supported_extentions)get_filename_index(filename);
    switch (e)
    {
    case BMP:
        return (*(extentions[BMP].read_func))(f, image);
    default:
        break;
    }
    return READ_ERROR;
}

enum write_status from_image(FILE* f, struct image* image, const char* filename){
    const enum supported_extentions e = (enum supported_extentions)get_filename_index(filename);
    switch (e)
    {
    case BMP:
        return (*(extentions[BMP].write_func))(f, image);
    default:
        break;
    }
    return WRITE_ERROR;
}