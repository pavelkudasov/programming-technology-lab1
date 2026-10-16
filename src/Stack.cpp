#include "Stack.h"
#include <iostream>
#include <stdexcept>

Stack::Stack() : Queue() {
    std::cout << "Stack #" << getId() << ": конструктор без параметров\n";
}

Stack::Stack(int capacity) : Queue(capacity) {
    std::cout << "Stack #" << getId() << ": конструктор с параметрами\n";
}

Stack::Stack(const Stack& other) : Queue(other) {
    std::cout << "Stack #" << getId() << ": конструктор копирования\n";
}

Stack& Stack::operator=(const Stack& other) {
    Queue::operator=(other);
    return *this;
}

Stack::~Stack() {
    std::cout << "Stack #" << getId() << ": деструктор\n";
}

const char* Stack::type() const { return "Stack"; }
Queue* Stack::clone() const { return new Stack(*this); }

void Stack::push(double value) {
    enqueue(value);
}

double Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Нельзя извлечь вершину: стек пуст.");
    }

    // Вершина - последнее число очереди. Переносим остальные числа за неё.
    // Например: [10, 20, 30] -> [20, 30, 10] -> [30, 10, 20].
    int rotations = size() - 1;
    for (int i = 0; i < rotations; i++) {
        rotate();
    }

    return dequeue();
}

double Stack::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Вершины нет: стек пуст.");
    }
    return get(size() - 1);
}
