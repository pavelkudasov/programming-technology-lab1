#include "Stack.h"
#include <iostream>

Stack::Stack() : Queue() {
    std::cout << "Stack " << this << ": конструктор без параметров\n";
}

Stack::Stack(double value) : Queue(value) {
    std::cout << "Stack " << this << ": конструктор с параметром\n";
}

Stack::Stack(const Stack& other) : Queue(other) {
    std::cout << "Stack " << this << ": конструктор копирования\n";
}

Stack& Stack::operator=(const Stack& other) {
    Queue::operator=(other);
    return *this;
}

Stack::~Stack() {
    std::cout << "Stack " << this << ": деструктор\n";
}

int Stack::getType() const { return 1; }
Queue* Stack::clone() const { return new Stack(*this); }
void Stack::push(double value) { enqueue(value); }

double Stack::pop() {
    for (int i = 0; i < getSize() - 1; i++) rotate();
    return dequeue();
}

double Stack::top() const { return get(getSize() - 1); }
