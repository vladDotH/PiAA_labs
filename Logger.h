#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdarg>

class Logger {
public:
    // Режимы логов (в release - не выводятся)
    enum MODE {
        DEBUG,
        RELEASE
    };

private:
    static MODE mode;
    // Отступ
    static int tab;

public:
    // Установка режима
    static void setMode(MODE m);
    // Получение режима
    static MODE getMode();

    // Вывод лога (ignoreTab - не печатать отступы)
    static void log(std::string str, bool ignoreTab = false);

    // Увеличить/Уменьшить отступ
    static void incTab();
    static void decTab();
};

// Макросы для оптимизации (чтобы строки лишний раз не складывались и не вызывалась функция log)
#define _log(...) if (Logger::getMode() == Logger::DEBUG) Logger::log(__VA_ARGS__);
#define _incTab() if (Logger::getMode() == Logger::DEBUG) Logger::incTab();
#define _decTab() if (Logger::getMode() == Logger::DEBUG) Logger::decTab();
#define _setMode(...) Logger::setMode(__VA_ARGS__);


#endif //LOGGER_H
