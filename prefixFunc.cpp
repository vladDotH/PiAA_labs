#include "prefixFunc.h"

// Вычисление префикс-функции
std::vector<int> prefFunc(const std::string &str) {
    _log("Calculation of Prefix-Function of string: \"" + str + "\"\n");
    _incTab();

    int n = str.size(), j;
    // Итоговый массив П.Ф. (заполнен нулями)
    std::vector<int> pf(n, 0);

    _log("Current prefix: (len:0)" + str.substr(0, 1) + "\n");
    _log("Value of border at 0th symbol = 0\n\n");
    for (int i = 1; i < n; ++i) {
    	_log("Current prefix: (len:" + std::to_string(i) + ") " + str.substr(0, i + 1) + "\n");    
        // Значение П.Ф. на предыдущей позиции.
        j = pf[i - 1];
        _log("Previos border: " + std::to_string(j) + "\n");
        // Сравниваем очередной символ в строке с символом на позиции какого-либо значения П.Ф.
        // до тех пор пока не найдётся совпадение, либо значение П.Ф. не дойдёт до нуля
        _incTab();
        _log("Comparing symbol at " + std::to_string(i) + " pos - '" + str[i] + "' with symbol at border value - '" + str[j] + "'\n");
        while (j > 0 && str[i] != str[j]) {
            j = pf[j - 1];
            _log("Occurence is not found, next border to compare: " + std::to_string(j) + "\n");
            _log("Comparing symbol at " + std::to_string(i) + " pos - '" + str[i] + "' with symbol at index of border value - '" + str[j] + "'\n");
        }
        // Если совпадение есть, очередное значение П.Ф. равно предыдущему + 1
        // Иначе i-ое значение остаётся нулевым
        if (str[i] == str[j]) {
            pf[i] = j + 1;
            _log("Occurency is found, value of border: " + std::to_string(j + 1) + "\n");
        } else {
             _log("Occurency is not found, value of border: 0 \n");
        }
		_decTab();
        
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
