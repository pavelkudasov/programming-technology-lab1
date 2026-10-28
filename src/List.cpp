#include "List.h"
#include <iostream>
#include <stdexcept>

List::List() : Queue() {
    std::cout << "List " << this << ": конструктор без параметров\n";
}

List::List(double value) : Queue(value) {
    std::cout << "List " << this << ": конструктор с параметром\n";
}

List::List(const List& other) : Queue(other) {
    std::cout << "List " << this << ": конструктор копирования\n";
}

List& List::operator=(const List& other) {
    Queue::operator=(other);
    return *this;
}

List::~List() {
    std::cout << "List " << this << ": деструктор\n";
}

int List::getType() const { return 3; }
Queue* List::clone() const { return new List(*this); }

void List::insert(int index, double value) {
    int n = getSize();
    if (index < 0 || index > n) {
        throw std::out_of_range("Неверная позиция вставки.");
    }
    for (int i = 0; i < index; i++) rotate();
    try {
        enqueue(value);
    } catch (...) {
        for (int i = 0; i < n - index; i++) rotate();
        throw;
    }
    // Возвращаем начало списка на место.
    for (int i = 0; i < n - index; i++) rotate();
}

double List::remove(int index) {
    int n = getSize();
    if (index < 0 || index >= n) {
        throw std::out_of_range("Неверный номер удаляемого элемента.");
    }
    for (int i = 0; i < index; i++) rotate();
    double value = dequeue();
    for (int i = 0; i < n - index - 1; i++) rotate();
    return value;
}
