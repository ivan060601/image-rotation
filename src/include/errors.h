#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <stdint.h>
#include "io.h"

enum rotate_status {
    ROTATE_SUCCESS = 30,
    ROTATE_ERROR
};

const char* describe_ru[] =
{
    [READ_OK] = "Файл успешно открыт\n",
    [READ_ERROR] = "Неизвестная ошибка в ходе считывания файла\n",
    [READ_INVALID_SIGNATURE] = "Неправильная сигнатура BMP-файла\n",
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