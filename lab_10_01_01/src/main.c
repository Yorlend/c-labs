/**
 * @file main.c
 * @author Klim Kornienko
 * @brief Тестирование функций для работы со списком
 * @version 0.1
 * @date 2021-11-18
 * 
 * Описание условия задачи:
 * 
 * Имитирование базы данных ветеринарной клиники:
 * 
 * Необходимо обеспечить симуляцию работы кошачьей ветеринарной клиники
 * 
 * Структура "пациента": имя / возраст / дата госпитализации
 * 
 * Данные о "пациентах" хранятся в файле, обеспечивается добавление,
 * обновление информации в файле, а также сортировку по возрасту 
 * и дате госпитализации и поиск. 
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "actions.h"


int main(int argc, char **argv)
{
    int status = EXIT_FAILURE;

    if (argc == 3 && strcmp(argv[1], "sort") == 0)
        status = action_sort(argv[2]);
    else if (argc == 4 && strcmp(argv[1], "find") == 0)
        status = action_find(argv[2], argv[3]);
    else if (argc == 3 && strcmp(argv[1], "insert") == 0)
        status = action_insert(argv[2]);

    return status;
}