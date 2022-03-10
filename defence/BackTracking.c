#include "BackTracking.h"

// Флаг отладки
int DEBUG = 0;

// Отстсуп на n пробелов
void printTab(int n) {
    while (n-- > 0)
        dbgPrintf("  ");
}

// Вывод решения
void printSln(Solution sln, int tabs) {
    printTab(tabs);
    dbgPrintf("Size: %d {\n", sln.size);
    for (int i = 0; i < sln.size; ++i) {
        printTab(tabs);
        dbgPrintf("%d, %d, %d\n", sln.list[i].y, sln.list[i].x, sln.list[i].R);
    }
    printTab(tabs);
    dbgPrintf("}\n");
}

// Вывод матрицы
void printMat(Matrix mat) {
    for (int i = 0; i < mat.n; ++i) {
        for (int j = 0; j < mat.m; ++j) {
            dbgPrintf("%d ", mat.arr[i][j]);
        }
        dbgPrintf("\n");
    }
}

// Конструктор матрицы
Matrix newMat(int n, int m) {
    Matrix mat = {n, m, malloc(sizeof(int *) * n)};
    for (int i = 0; i < n; ++i)
        mat.arr[i] = calloc(m, sizeof(int));
    return mat;
}

// Вставка квадрата в матрицу
void insert(Matrix mat, Square sq, int item) {
    for (int y = sq.y; y < sq.y + sq.R; ++y)
        for (int x = sq.x; x < sq.x + sq.R; ++x)
            mat.arr[y][x] = item;
}

// Поиск свободной ячейки (сверху-слева)
Square findFree(Matrix mat) {
    for (int i = 0; i < mat.n; ++i)
        for (int j = 0; j < mat.m; ++j)
            if (mat.arr[i][j] == 0)
                return (Square) {i, j, 0};
    // Если не нашлось
    return (Square) {-1, -1, 0};
}

// Проверка возможности вставить квадрат в матрицу
int check(Matrix mat, Square sq) {
    // Проверка вместимости квадрата в матрицу
    if (sq.x + sq.R > mat.m || sq.y + sq.R > mat.n)
        return 0;
    for (int i = sq.y; i < sq.y + sq.R; ++i) {
        for (int j = sq.x; j < sq.x + sq.R; ++j) {
            if (mat.arr[i][j] != 0)
                return 0;
        }
    }
    return 1;
}

// Рекурсивный шаг
void recStep(int N, Solution sln, Matrix mat, Solution *best, int depth) {
    // Завершение неоптимальной ветки решения (если решение уже длиннее лучшего)
    if (sln.size >= best->size) {
	printTab(depth);
	dbgPrintf("Branch size more than best, returning\n");
        return;
    }
    // Свободная клетка
    Square cell = findFree(mat);
    // Если не найдена
    if (cell.y == -1) {
        // Новое кратчайшее решение
        if (sln.size < best->size) {
            dbgPrintf("\n");
            printTab(depth);
            dbgPrintf("New record:\n");
            printSln(sln, depth);
            dbgPrintf("\n");
            memcpy(best->list, sln.list, sizeof(Square) * sln.size);
            best->size = sln.size;
        }
    } else {
        // Перебор квадратов которые можно вставить
        for (cell.R = N / 2 + N % 2; cell.R > 0; --cell.R) {
            if (check(mat, cell)) {
                // Вставка
                insert(mat, cell, 1);
                sln.list[sln.size++] = cell;
                printTab(depth);
                dbgPrintf("Inserting square: (%d %d %d)\n", cell.y, cell.x, cell.R);
                // Новый шаг в глубину
                recStep(N, sln, mat, best, depth + 1);
                // Откат к предыдущему состоянию (чтобы не создавать новую матрицу и массив решений на каждом шаге)
                insert(mat, cell, 0);
                sln.size--;
                printTab(depth);
                dbgPrintf("Drop square: (%d %d %d)\n", cell.y, cell.x, cell.R);
            }
        }
    }
}

// Базовое решение
Solution solve(int N) {
    // Поиск минимального простого делителя, далее алгоритм будет работать с ним
    // А решение просто умножится на оставшийся множитель (remain)
    int minDiv = 2;
    while (N % minDiv != 0)
        minDiv++;
    int remain = N / minDiv;
    N = minDiv;
    dbgPrintf("min divisor: %d\n", minDiv);

    // Лучшее базовое решение (все единичные квадраты)
    Solution best = {N * N, N * N, malloc(sizeof(Square) * N * N)};
    for (int i = 0; i < best.size; ++i) {
        best.list[i] = (Square) {i / N, i % N, 1};
    }

    // Буферное решение
    Solution sln = {N * N, 0, malloc(sizeof(Square) * N * N)};
    // Матрица
    Matrix mat = newMat(N, N);

    // Начальная оптимизация
    int half = N / 2 + N % 2;
    sln.list[sln.size++] = (Square) {0, 0, half};
    sln.list[sln.size++] = (Square) {half, 0, half - 1};
    sln.list[sln.size++] = (Square) {0, half, half - 1};
    for (int i = 0; i < sln.size; ++i) {
        insert(mat, sln.list[i], 1);
    }

    dbgPrintf("Initial matrix:\n");
    printMat(mat);
    dbgPrintf("\n");

    // запуск рекурсии
    recStep(N, sln, mat, &best, 0);

    // Обратное масштабирование решения
    if (remain != 1) {
        for (int i = 0; i < best.size; ++i) {
            best.list[i].x *= remain;
            best.list[i].y *= remain;
            best.list[i].R *= remain;
        }
    }
    free(sln.list);
    free(mat.arr);
    return best;
}

// Решение в случае прямоугольника
Solution advancedSolve(int N, int M, int *count) {
    // Аналогично базовое лучшее решение - все квадраты 1х1
    Solution best = {N * M, N * M, malloc(sizeof(Square) * N * M)};
    for (int i = 0; i < best.size; ++i) {
        best.list[i] = (Square) {i / N, i % N, 1};
    }

    // Буферное решение
    Solution sln = {N * M, 0, malloc(sizeof(Square) * N * M)};
    // Матрица
    Matrix mat = newMat(N, M);
    // Количество вариантов минимального замощения
    *count = 0;
    // запуск рекурсии
    advancedRecStep(N, M, sln, mat, &best, count, 0);
    free(sln.list);
    free(mat.arr);
    return best;
}

// Шаг в случае прямоугольника
void advancedRecStep(int N, int M, Solution sln, Matrix mat, Solution *best, int *count, int depth) {
    // Завершение неоптимальной ветки решения (если решение уже длиннее лучшего)
    if (sln.size > best->size)  {
	printTab(depth);
	dbgPrintf("Branch size more than best, returning\n");
        return;
    }
    // Свободная клетка
    Square cell = findFree(mat);
    // Если не найдена
    if (cell.y == -1) {
        // Инкремент количества минимальных замощений
        if (sln.size == best->size) {
            (*count) ++;
             dbgPrintf("\n");
            printTab(depth);
            dbgPrintf("Equal solution found:\n");
            printSln(sln, depth);
            dbgPrintf("\n");
        }
        // Новое кратчайшее решение
        if (sln.size < best->size) {
            (*count) = 1;
            dbgPrintf("\n");
            printTab(depth);
            dbgPrintf("New record:\n");
            printSln(sln, depth);
            dbgPrintf("\n");
            memcpy(best->list, sln.list, sizeof(Square) * sln.size);
            best->size = sln.size;
        }
    } else {
        int min = (N > M ? M : N);
        // Перебор квадратов которые можно вставить
        for (cell.R = min - 1; cell.R > 0; --cell.R) {
            if (check(mat, cell)) {
                // Вставка
                insert(mat, cell, 1);
                sln.list[sln.size++] = cell;
                printTab(depth);
                dbgPrintf("Inserting square: (%d %d %d)\n", cell.y, cell.x, cell.R);
                // Новый шаг в глубину
                advancedRecStep(N, M, sln, mat, best, count, depth + 1);
                // Откат к предыдущему состоянию (чтобы не создавать новую матрицу и массив решений на каждом шаге)
                insert(mat, cell, 0);
                sln.size--;
                printTab(depth);
                dbgPrintf("Drop square: (%d %d %d)\n", cell.y, cell.x, cell.R);
            }
        }
    }
}
