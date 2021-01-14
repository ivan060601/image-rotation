#include <stdbool.h>
#include <stdio.h>

#include "bmp.h"
#include "util.h"
#include "errors.h"
#include "io.h"
#include "image_structure.h"
#include "filters.h"


void usage() {
    //Напоминаем пользователю, как же пользоваться программой
    fprintf(stderr, "Usage: ./print_header BMP_FILE_NAME filter_name\n"); 
}

int main( int argc, char** argv ) {
    //Проверяем количество введенных пользователем аргументов
    if (argc != 3) usage();
    if (argc < 3) err(describe_ru[NOT_ENOUGHT_ARGS]);
    if (argc > 3) err(describe_ru[TOO_MANY_ARGS]);

    //Открываем файл
    FILE* f = fopen( argv[1], "rb" ); 

    struct image image = {0};

    enum read_status read_result = from_bmp(f, &image);
    if (read_result != READ_OK)
        err(describe_ru[read_result]);
    printf("%s", describe_ru[READ_OK]);

    //ЗАКРЫВАЕМ ФАЙЛ
    fclose(f);

    //struct image new_image = rotate_and_create_new_image(&image);
    rotate_existing_image(&image);

    //Сохраняем новый файл
    FILE* fout;
    if ((fout = fopen("out.bmp", "wb"))==NULL)
        err(describe_ru[WRITE_ERROR]);

    enum write_status write_result = to_bmp(fout, &image);
    if (write_result != WRITE_OK)
        err(describe_ru[write_result]);
    printf("%s", describe_ru[WRITE_OK]);

    fclose(fout);
    return 0;
}
