#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "Stack.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

double readNumber(const char* prompt) {
    char text[256];

    for (;;) {
        std::cout << prompt;
        std::cin.getline(text, sizeof(text));

        if (std::cin.eof()) {
            throw std::runtime_error("Ввод завершён.");
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Слишком длинная строка. Повторите ввод.\n";
            continue;
        }

        char* end;
        errno = 0;
        double value = std::strtod(text, &end);
        bool hasNumber = end != text;

        // После числа разрешены только пробельные символы.
        while (*end == ' ' || *end == '\t' || *end == '\r') end++;

        if (hasNumber && *end == '\0' && std::isfinite(value)
            && errno != ERANGE) {
            return value;
        }

        std::cout << "Ошибка: введите одно конечное число через точку.\n";
    }
}

int readInteger(const char* prompt, int min, int max) {
    for (;;) {
        double value = readNumber(prompt);
        if (value >= min && value <= max && std::floor(value) == value) {
            return static_cast<int>(value);
        }
        std::cout << "Нужно целое число от " << min << " до " << max << ".\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "Лабораторная работа 1. Вариант 11\n"
              << "Прототип: стек на основе очереди\n";

    try {
        int capacity = readInteger("Начальная вместимость стека: ",
                                   1, Queue::MAX_CAPACITY);
        Stack stack(capacity);

        for (;;) {
            std::cout << "\n1. Добавить число\n"
                      << "2. Извлечь вершину\n"
                      << "3. Посмотреть вершину\n"
                      << "4. Показать стек\n"
                      << "0. Выход\n";

            try {
                int choice = readInteger("Выбор: ", 0, 4);
                if (choice == 0) break;

                if (choice == 1) {
                    double value = readNumber("Число: ");
                    stack.push(value);
                    std::cout << "Число добавлено.\n";
                } else if (choice == 2) {
                    double value = stack.pop();
                    std::cout << "Извлечено: " << value << '\n';
                } else if (choice == 3) {
                    double value = stack.top();
                    std::cout << "Вершина: " << value << '\n';
                } else if (choice == 4) {
                    std::cout << stack << '\n';
                    std::cout << "Последнее число в скобках - вершина.\n";
                }
            } catch (const std::exception& error) {
                if (std::cin.eof()) throw;
                std::cout << "Ошибка: " << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cout << error.what() << '\n';
        return std::cin.eof() ? 0 : 1;
    }

    return 0;
}
