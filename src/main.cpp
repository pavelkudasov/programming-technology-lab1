#include "Keeper.h"
#include "Stack.h"
#include "Deque.h"
#include "List.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

double readNumber(const char* prompt) {
    std::cout << prompt;
    double value;
    if (!(std::cin >> value)) {
        if (std::cin.eof()) throw std::runtime_error("Ввод завершён.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Нужно ввести число через точку.");
    }
    char symbol;
    bool valid = true;
    while (std::cin.get(symbol) && symbol != '\n') {
        if (symbol != ' ' && symbol != '\t' && symbol != '\r') valid = false;
    }
    if (!valid || !std::isfinite(value)) {
        throw std::runtime_error("Нужно ввести одно конечное число.");
    }
    return value;
}

int readInt(const char* prompt, int min, int max) {
    double value = readNumber(prompt);
    if (std::floor(value) != value) {
        throw std::invalid_argument("Нужно ввести целое число без дробной части.");
    }
    if (value < min || value > max) {
        std::cout << "Допустимый диапазон: от " << min << " до " << max << ".\n";
        throw std::out_of_range("Число вне допустимого диапазона.");
    }
    return static_cast<int>(value);
}

int chooseObject(Keeper& keeper) {
    if (keeper.getSize() == 0) throw std::runtime_error("Объектов пока нет.");
    for (int i = 0; i < keeper.getSize(); i++) {
        std::cout << i + 1 << ". " << keeper.get(i) << '\n';
    }
    return readInt("Номер объекта: ", 1, keeper.getSize()) - 1;
}

void addObject(Keeper& keeper) {
    int type = readInt("1 - стек, 2 - дек, 3 - список: ", 1, 3);
    int filled = readInt("0 - пустой, 1 - с одним числом: ", 0, 1);
    double value = 0;
    if (filled == 1) value = readNumber("Первое число: ");
    if (type == 1) {
        Stack object = filled ? Stack(value) : Stack();
        keeper.add(object);
    } else if (type == 2) {
        Deque object = filled ? Deque(value) : Deque();
        keeper.add(object);
    } else {
        List object = filled ? List(value) : List();
        keeper.add(object);
    }
}

void workWithObject(Queue& object) {
    for (;;) {
        std::cout << '\n' << object << '\n'
                  << "У стека вершина справа, у дека и списка начало слева.\n"
                  << "1. Добавить число\n2. Удалить число\n"
                  << "3. Посмотреть число\n4. Изменить число\n"
                  << "5. Очистить\n0. Назад\n";
        try {
            int choice = readInt("Выбор: ", 0, 5);
            if (choice == 0) return;
            int type = object.getType();
            if (choice == 1) {
                int position = 0;
                if (type == 2) position = readInt("1 - начало, 2 - конец: ", 1, 2);
                if (type == 3) {
                    std::cout << "Позиции вставки: от 1 до " << object.getSize() + 1 << '\n';
                    position = readInt("Позиция: ", 1, object.getSize() + 1) - 1;
                }
                double value = readNumber("Число: ");
                if (type == 1) static_cast<Stack&>(object).push(value);
                else if (type == 2) {
                    Deque& deque = static_cast<Deque&>(object);
                    if (position == 1) deque.pushFront(value);
                    else deque.pushBack(value);
                } else static_cast<List&>(object).insert(position, value);
            } else if (choice == 2 || choice == 3) {
                if (object.getSize() == 0) throw std::runtime_error("Контейнер пуст.");
                double value;
                if (type == 1) {
                    Stack& stack = static_cast<Stack&>(object);
                    value = choice == 2 ? stack.pop() : stack.top();
                } else if (type == 2) {
                    int side = readInt("1 - начало, 2 - конец: ", 1, 2);
                    Deque& deque = static_cast<Deque&>(object);
                    if (choice == 2) value = side == 1 ? deque.popFront() : deque.popBack();
                    else value = side == 1 ? deque.front() : deque.back();
                } else {
                    int index = readInt("Номер элемента: ", 1, object.getSize()) - 1;
                    List& list = static_cast<List&>(object);
                    value = choice == 2 ? list.remove(index) : list.get(index);
                }
                std::cout << "Число: " << value << '\n';
            } else if (choice == 4) {
                if (object.getSize() == 0) throw std::runtime_error("Контейнер пуст.");
                int index = readInt("Номер элемента слева: ", 1, object.getSize()) - 1;
                double value = readNumber("Новое число: ");
                object.set(index, value);
            } else object.clear();
        } catch (const std::exception& error) {
            if (std::cin.eof()) throw;
            std::cout << "Ошибка: " << error.what() << '\n';
        }
    }
}

void readFilename(char* filename, int size) {
    std::cout << "Имя файла (например data.txt): ";
    std::cin.getline(filename, size);
    if (!std::cin) {
        if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        throw std::runtime_error("Не удалось прочитать имя файла.");
    }
    if (filename[0] == '\0') throw std::runtime_error("Имя файла пустое.");
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Keeper keeper;
    std::cout << "Лабораторная работа 1. Вариант 11\n";
    for (;;) {
        std::cout << "\n1. Создать объект\n2. Удалить объект\n"
                  << "3. Показать все объекты\n4. Работать с объектом\n"
                  << "5. Скопировать объект\n6. Сохранить в файл\n"
                  << "7. Загрузить из файла (заменить текущие данные)\n0. Выход\n";
        try {
            int choice = readInt("Выбор: ", 0, 7);
            if (choice == 0) break;
            if (choice == 1) addObject(keeper);
            else if (choice == 2) keeper.remove(chooseObject(keeper));
            else if (choice == 3) {
                if (keeper.getSize() == 0) std::cout << "Объектов пока нет.\n";
                for (int i = 0; i < keeper.getSize(); i++) {
                    std::cout << i + 1 << ". " << keeper.get(i) << '\n';
                }
            } else if (choice == 4) workWithObject(keeper.get(chooseObject(keeper)));
            else if (choice == 5) keeper.add(keeper.get(chooseObject(keeper)));
            else {
                char filename[256];
                readFilename(filename, sizeof(filename));
                if (choice == 6) keeper.save(filename);
                else keeper.load(filename);
                std::cout << "Готово.\n";
            }
        } catch (const std::exception& error) {
            if (std::cin.eof()) break;
            std::cout << "Ошибка: " << error.what() << '\n';
        }
    }
    return 0;
}
