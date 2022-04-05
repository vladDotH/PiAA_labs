#include <iostream>
#include <vector>
#include <string>
#include "prefixFunc.h"
#include "Logger.h"

// Вычисление индекса сдвига (s1 - сдвиг s2)
int cycleShift(const std::string &s1, const std::string &s2, char delimiter = '|') {
    _log("Detection of possible cycle shift from \"" + s2 + "\" to \"" + s1 + "\"\n");
    _incTab();

    int l1 = s1.size();
    // Если длины строк различны, дальше сравнивать бессмысленно
    if (l1 != s2.size()) {
        _decTab();
        _log("Strings sizes are not equal => -1");
        return -1;
    }

    // Используем подход аналогичный КМП, конкатенируем строки с разделителем
    // (только теперь s2 будет искаться в s1)
    std::string S = s2 + delimiter + s1;
    // П.Ф. от полученной строки
    std::vector<int> pf = prefFunc(S);
    // Нас интересует значение П.Ф. только на последнем символе, оно будет равно
    // количеству совпавших символов из начала второй строки с концом первой строки
    int j = pf.back();

    _log("Value of P.F. at last symbol = " + std::to_string(j) + "\n");

    // Остаётся сравнить оставшиеся части: начало первой строки и конец второй
    _decTab()
    _log("Compare remain parts : \"" + s1.substr(0, l1 - j) + "\" and \"" + s2.substr(j) + "\"");
    if (s1.substr(0, l1 - j) == s2.substr(j)) {
        _log(" (equal) => " + std::to_string(j) + " is shift index\n\n", true);
        return l1 - j;
    }
    else {
        _log(" (not equal) => s1 is not cycle shift of s2\n\n", true);
        return -1;
    }
}

int main() {
    _setMode(Logger::DEBUG);
    // B - строка, A - её предполагаемый циклический сдвиг
    std::string A, B;
    std::cin >> A >> B;
    std::cout << cycleShift(A, B);
}