#include <stdbool.h>
#include <stdio.h>

#include "bmp.h"
#include "util.h"
#include "errors.h"
#include "io.h"
#include "image_structure.h"


void usage() {
    //Напоминаем пользователю, как же пользоваться программой
    fprintf(stderr, "Usage: ./print_header BMP_FILE_NAME\n"); 
}

int main( int argc, char** argv ) {
    //Проверяем количество введенных пользователем аргументов
    if (argc != 2) usage();
    if (argc < 2) err(describe_ru[NOT_ENOUGHT_ARGS]);
    if (argc > 2) err(describe_ru[TOO_MANY_ARGS]);

    //Открываем файл
    FILE* f = fopen( argv[1], "rb" ); 

    struct image image = {0};
    image_malloc(&image);

    enum read_status read_result = from_bmp(f, &image);
    if (read_result != READ_OK)
        err(describe_ru[read_result]);
    printf("%s", describe_ru[READ_OK]);

    //ЗАКРЫВАЕМ ФАЙЛ
    fclose(f);

    //Переворачиваем image->data


    //Сохраняем новый файл
    FILE* fout;
    if ((fout = fopen("out.bmp", "wb"))==NULL)
        err(describe_ru[WRITE_ERROR]);

    enum write_status write_result = to_bmp(fout, &image);
    if (write_result != WRITE_OK)
        err(describe_ru[write_result]);
    printf("%s", describe_ru[WRITE_OK]);

    fclose(fout);

    //Это чисто для дебага
    /*
    struct bmp_header h = { 0 };
    if (read_header_from_file( argv[1], &h )) {
        bmp_header_print( &h, stdout );
    }
    else {
        err( "Failed to open BMP file or reading header.\n" );
    }
    */
    return 0;
}
