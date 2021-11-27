# Функциональные тесты к РК (задача 3, вариант 2) динамические матрицы

## Входные данные
    матрица и её размерности

## Выходные данные
    матрица

## Позитивные тесты
 - 01 - обычный тест
 - 02 - элемент с четной суммой цифр один
 - 03 - все элементы с четной суммой цифр
 - 04 - четные элементы при обходе по столбцам уже упорядочены по убыванию
 - 05 - четные элементы при обходе по строкам упорядочены по возрастанию

## Негативные тесты
 - 01 - не существующий файл
 - 02 - пустой файл
 - 03 - отрицательное количество строк
 - 04 - отрицательное количество столбцов
 - 05 - элемент массива не число
 - 06 - элемент массива -- вещественное число

## Проверка Valgrind:

### Негативные
-----------------------------
```
==20784== Command: ./app.exe in.txt
==20784== 
incorrect matrix
==20784== 
==20784== HEAP SUMMARY:
==20784==     in use at exit: 0 bytes in 0 blocks
==20784==   total heap usage: 3 allocs, 3 frees, 5,592 bytes allocated
==20784== 
==20784== All heap blocks were freed -- no leaks are possible
==20784== 
==20784== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
-----------------------------

### Позитивные
```
==20981== Memcheck, a memory error detector
==20981== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20981== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==20981== Command: ./app.exe data.txt
==20981== 
1 -8 47 22
81 45 54 61
93 9 10 -11
75 -43 33 -3
==20981== 
==20981== HEAP SUMMARY:
==20981==     in use at exit: 0 bytes in 0 blocks
==20981==   total heap usage: 9 allocs, 9 frees, 5,712 bytes allocated
==20981== 
==20981== All heap blocks were freed -- no leaks are possible
==20981== 
==20981== For lists of detected and suppressed errors, rerun with: -s
==20981== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```