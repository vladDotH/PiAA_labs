#include "Logger.h"

Logger::MODE Logger::mode = RELEASE;
int Logger::tab = 0;

void Logger::setMode(Logger::MODE m) {
    mode = m;
}

void Logger::log(std::string str, bool ignoreTabs) {
    if (mode == DEBUG) {
        if (!ignoreTabs)
            for (int i = 0; i < tab; ++i) {
                std::cout << '\t';
            }
        std::cout << str;
    }
}

void Logger::incTab() {
    tab++;
}

void Logger::decTab() {
    tab--;
}

Logger::MODE Logger::getMode() {
    return mode;
}
