#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdarg.h>

// Флаг отладки
extern int DEBUG;

// Отладочный вывод
#define dbgPrintf(...) if (DEBUG) printf(__VA_ARGS__);

// Квадрат
typedef struct Square {
    int y, x, R;
} Square;

// Список квадратов (решение)
typedef struct Solution {
    int mem, size;
    Square *list;
} Solution;

// Вывод решения
void printSln(Solution sln);

// Целочисленная матрица n на m
typedef struct Matrix {
    int n, m;
    int **arr;
} Matrix;

// Вывод матрицы
void printMat(Matrix mat);

// Конструктор матрицы
Matrix newMat(int n, int m);

// Вставка квадрата в матрицу
void insert(Matrix mat, Square sq, int item);

// Поиск свободной ячейки (сверху-слева)
Square findFree(Matrix mat);

// Проверка возможности вставить квадрат в матрицу
int check(Matrix mat, Square sq);

// Рекурсивный шаг
void recStep(int N, Solution sln, Matrix mat, Solution *best);

// Базовое решение
Solution solve(int N);

// Решение в случае прямоугольника
Solution advancedSolve(int N, int M, int *count);

// Шаг в случае прямоугольника
void advancedRecStep(int N, int M, Solution sln, Matrix mat, Solution *best, int *count);

#endif //BACKTRACKING_H
