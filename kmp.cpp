#include <iostream>
#include <vector>
#include <string>
#include "prefixFunc.h"

// Поиск вхождений s1 в s2 (алгоритм КМП)
std::vector<int> kmp(const std::string &s1, const std::string &s2, char delimiter = '|') {
    _log("Finding occurrences of \"" + s1 + "\" in \"" + s2 + "\"\n");
    _incTab();

    // Длины переданных строк
    int l1 = s1.size(), l2 = s2.size();
    // Объединённая разделителем строка
    std::string S = s1 + delimiter + s2;
    // Вычисление П.Ф. от объединённой строки
    std::vector<int> pf = prefFunc(S);
    // Массив вхождений s1 в s2
    std::vector<int> pos;

    _log("Iterate over prefix-function:\n");
    _incTab();
    for (int i = l1 + 1; i < l1 + 1 + l2; ++i) {
        _log("Current substring: " + s2.substr(0, i - l1) + "\n");

        // Если П.Ф. на i-ом элемента равна длине первой строки, значит i-ый элемент
        // - последний элемент вхождения s1 в s2.
        if (pf[i] == l1) {
            // А индекс начала вхождения будет вычисляться
            // (i - l1 + 1) - начало вхождения s1 в строке S
            // (- l1 - 1) - вычесть длину присоединённой s1 и разделителя
            // Итого (i - 2 * l1)
            pos.push_back(i - 2 * l1);
            _log("Occurrence is found at symbol " + std::to_string(i - l1 - 1) +
                 " (beginning of occurrence at " + std::to_string(i - 2 * l1) + ")\n");
        }
        _log("\n", true);
    }
    _decTab();
    _decTab();
    _log("Final occurrences = [");
    for (int i = 0; i < pos.size(); ++i) {
        _log(std::to_string(pos[i]));
        if (i != pos.size() - 1)
            _log(", ");
    }
    _log("]\n\n");

    return pos;
}

int main() {
    _setMode(Logger::DEBUG);

    // P - шаблон, T - текст
    std::string P, T;
    std::cin >> P >> T;

    // Массив вхождений
    std::vector<int> pos = kmp(P, T);
    for (int i = 0; i < pos.size(); ++i) {
        std::cout << pos[i];
        if (i != pos.size() - 1)
            std::cout << ',';
    }
    // Если пустой -> -1
    if (!pos.size())
        std::cout << -1;

    return 0;
}