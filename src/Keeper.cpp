#include "Keeper.h"
#include "Stack.h"
#include "Deque.h"
#include "List.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

Keeper::Keeper() : objects(nullptr), count(0) {
    std::cout << "Keeper " << this << ": конструктор без параметров\n";
}

Keeper::Keeper(const Queue& object) : objects(nullptr), count(0) {
    add(object);
    std::cout << "Keeper " << this << ": конструктор с параметром\n";
}

Keeper::Keeper(const Keeper& other) : objects(nullptr), count(0) {
    try {
        for (int i = 0; i < other.count; i++) add(*other.objects[i]);
    } catch (...) {
        clear();
        throw;
    }
    std::cout << "Keeper " << this << ": конструктор копирования\n";
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        clear();
        objects = copy.objects;
        count = copy.count;
        copy.objects = nullptr;
        copy.count = 0;
    }
    return *this;
}

Keeper::~Keeper() {
    clear();
    std::cout << "Keeper " << this << ": деструктор\n";
}

int Keeper::getSize() const { return count; }

Queue& Keeper::get(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Неверный номер объекта.");
    }
    return *objects[index];
}

void Keeper::add(const Queue& object) {
    Queue** copy = new Queue*[count + 1];
    for (int i = 0; i < count; i++) copy[i] = objects[i];
    try {
        copy[count] = object.clone();
    } catch (...) {
        delete[] copy;
        throw;
    }
    delete[] objects;
    objects = copy;
    count++;
}

void Keeper::remove(int index) {
    get(index); // Проверка номера перед удалением.
    delete objects[index];
    for (int i = index; i < count - 1; i++) objects[i] = objects[i + 1];
    count--;
}

void Keeper::clear() {
    for (int i = 0; i < count; i++) delete objects[i];
    delete[] objects;
    objects = nullptr;
    count = 0;
}

void Keeper::save(const char* filename) const {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Не удалось открыть файл для записи.");
    file << std::setprecision(std::numeric_limits<double>::max_digits10);
    file << count << '\n';
    for (int i = 0; i < count; i++) {
        file << objects[i]->getType() << ' ' << objects[i]->getSize() << '\n';
        for (int j = 0; j < objects[i]->getSize(); j++) {
            file << objects[i]->get(j) << ' ';
        }
        file << '\n';
    }
    file.close();
    if (!file) throw std::runtime_error("Ошибка записи в файл.");
}

void Keeper::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Не удалось открыть файл для чтения.");
    int objectCount;
    if (!(file >> objectCount) || objectCount < 0) {
        throw std::runtime_error("Неверное количество объектов в файле.");
    }

    // Старые данные сохраняются, пока весь файл не будет прочитан.
    Keeper loaded;
    for (int i = 0; i < objectCount; i++) {
        int type, size;
        if (!(file >> type >> size) || size < 0 || type < 1 || type > 3) {
            throw std::runtime_error("Неверный тип или размер объекта в файле.");
        }
        Queue* object = nullptr;
        if (type == 1) object = new Stack;
        else if (type == 2) object = new Deque;
        else object = new List;

        try {
            for (int j = 0; j < size; j++) {
                double value;
                if (!(file >> value)) {
                    throw std::runtime_error("Не удалось прочитать число из файла.");
                }
                if (type == 1) static_cast<Stack*>(object)->push(value);
                else if (type == 2) static_cast<Deque*>(object)->pushBack(value);
                else static_cast<List*>(object)->insert(j, value);
            }
            loaded.add(*object);
        } catch (...) {
            delete object;
            throw;
        }
        delete object;
    }
    file >> std::ws;
    if (!file.eof()) throw std::runtime_error("В файле есть лишние данные.");

    clear();
    objects = loaded.objects;
    count = loaded.count;
    loaded.objects = nullptr;
    loaded.count = 0;
}
