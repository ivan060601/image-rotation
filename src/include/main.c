#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "errors.h"
#include "io.h"
#include "image_structure.h"
#include "filters.h"

struct filter_text{
    filter* f;
    const char* name;
};

struct filter_text filters[] = {
    [GRAYSCALE] = {grayscale_filter, "grayscale"},
    [INVERSE] = {inverse, "inverse"},
    [SEPIA] = {sepia, "sepia"},
    [LAPLASSIAN] = {laplassian, "laplassian"},
    [ROTATE_EX] = {NULL, "rotate-ex"},
    [ROTATE_SAVE] = {NULL, "rotate-s"}
};

int get_filter_id(const char* fil){
    for (int i = START_FIL+1; i < END_FIL; i++)
    {
        if(strcmp(filters[i].name, fil) == 0){
            return i;
        }
    }
    return -1;
}

void save(struct image* image){
    FILE* fout;
    if ((fout = fopen("out.bmp", "wb"))==NULL)
        err(describe_ru[WRITE_ERROR]);

    enum write_status write_result = from_image(fout, image, "out.bmp");
    if (write_result != WRITE_OK)
        err(describe_ru[write_result]);
    printf("%s", describe_ru[WRITE_OK]);

    fclose(fout);
}

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

    enum read_status read_result = to_image(f, &image, argv[1]);
    if (read_result != READ_OK)
        err(describe_ru[read_result]);
    printf("%s", describe_ru[READ_OK]);

    //ЗАКРЫВАЕМ ФАЙЛ
    fclose(f);

    const enum available_filters desired_filter = (enum available_filters)get_filter_id(argv[2]);
    struct image new_image = {0};
    
    switch (desired_filter)
    {
    case GRAYSCALE:
    case INVERSE:
    case SEPIA:
    case LAPLASSIAN:
        (*(filters[desired_filter].f))(&image);
        save(&image);
        break;
    case ROTATE_SAVE:
        new_image = rotate(&image);
        save(&new_image);
        break;
    case ROTATE_EX:
        rotate_existing_image(&image);
        save(&image);    
        break;
    default:
        err("Неверный фильтр\n");
        break;
    }

    return 0;
}
