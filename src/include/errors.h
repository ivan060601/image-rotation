#include <stdint.h>

#ifndef _ERRORS_H_
#define _ERRORS_H_

enum read_status  {
    READ_OK = 10,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    NOT_ENOUGHT_ARGS,
    TOO_MANY_ARGS
};

enum  write_status  {
    WRITE_OK = 20,
    WRITE_ERROR
};

enum rotate_status {
    ROTATE_SUCCESS = 30,
    ROTATE_ERROR
};

const char* describe_ru[] =
{
    [READ_OK] = "Файл успешно открыт\n",
    [READ_INVALID_SIGNATURE] = "Не особо понял, когда она может появиться\n",
    [READ_INVALID_BITS] = "Видимо, картинка битая\n",
    [READ_INVALID_HEADER] = "Недопустимый заголовок BMP-файла\n",
    [WRITE_OK] = "Файл успешно записан\n",
    [WRITE_ERROR] = "Ошибка записи файла\n",
    [NOT_ENOUGHT_ARGS] = "Недостаточно входных параметров для запуска программы\n",
    [TOO_MANY_ARGS] = "Слишком много входных параметров для запуска программы\n",
    [ROTATE_SUCCESS] = "Картинка успешно повернута\n",
    [ROTATE_ERROR] = "Ошибка в ходе поворачивания изображения\n"
};


#endif