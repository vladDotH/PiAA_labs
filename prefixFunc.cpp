#include "prefixFunc.h"

// Вычисление префикс-функции
std::vector<int> prefFunc(std::string str) {
    _log("Calculation of Prefix-Function of string: \"" + str + "\"\n");
    _incTab();

    int n = str.size(), j;
    // Итоговый массив П.Ф. (заполнен нулями)
    std::vector<int> pf(n, 0);

    _log("Current prefix: " + str.substr(0, 1) + "\n");
    _log("Value of border at 0th symbol = 0\n\n");
    for (int i = 1; i < n; ++i) {
        // Значение П.Ф. на предыдущей позиции.
        j = pf[i - 1];
        // Сравниваем очередной символ в строке с символом на позиции какого-либо значения П.Ф.
        // до тех пор пока не найдётся совпадение, либо значение П.Ф. не дойдёт до нуля
        while (j > 0 && str[i] != str[j])
            j = pf[j - 1];
        // Если совпадение есть, очередное значение П.Ф. равно предыдущему + 1
        // Иначе i-ое значение остаётся нулевым
        if (str[i] == str[j])
            pf[i] = j + 1;

        _log("Current prefix: " + str.substr(0, i + 1) + "\n");
        _log("Value of border at " + std::to_string(i) + "th symbol = " + std::to_string(pf[i]) + "\n\n");
    }
    _decTab();
    _log("Final P.F.: [");
    for (int i = 0; i < pf.size(); ++i) {
        _log(std::to_string(pf[i]), true);
        if (i != pf.size() - 1)
            _log(", ", true);
    }
    _log("]\n\n", true);

    return pf;
}