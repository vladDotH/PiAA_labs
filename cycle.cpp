#include <iostream>
#include <vector>
#include <string>
#include "prefixFunc.h"

// Вычисление индекса сдвига (s1 - сдвиг s2)
int cycleShift(std::string s1, std::string s2, char delimiter = '|' ) {
    int l1 = s1.size();
    // Если длины строк различны, дальше сравнивать бессмысленно
    if (l1 != s2.size())
        return -1;
    // Используем подход аналогичный КМП, конкатенируем строки с разделителем
    // (только теперь s2 будет искаться в s1)
    std::string S = s2 + delimiter + s1;
    // П.Ф. от полученной строки
    std::vector<int> pf = prefFunc(S);
    // Нас интересует значение П.Ф. только на последнем символе, оно будет равно
    // количеству совпавших символов из начала второй строки с концом первой строки
    int j = pf.back();
    // Остаётся сравнить оставшиеся части: начало первой строки и конец второй
    return s1.substr(0, l1 - j) == s2.substr(j) ? l1 - j : -1;
}

int main() {
    // B - строка, A - её предполагаемый циклический сдвиг
    std::string A, B;
    std::cin >> A >> B;
    std::cout << cycleShift(A, B);
}