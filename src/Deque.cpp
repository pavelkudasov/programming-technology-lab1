#include "Deque.h"
#include <iostream>

Deque::Deque() : Queue() {
    std::cout << "Deque " << this << ": конструктор без параметров\n";
}

Deque::Deque(double value) : Queue(value) {
    std::cout << "Deque " << this << ": конструктор с параметром\n";
}

Deque::Deque(const Deque& other) : Queue(other) {
    std::cout << "Deque " << this << ": конструктор копирования\n";
}

Deque& Deque::operator=(const Deque& other) {
    Queue::operator=(other);
    return *this;
}

Deque::~Deque() {
    std::cout << "Deque " << this << ": деструктор\n";
}

int Deque::getType() const { return 2; }
Queue* Deque::clone() const { return new Deque(*this); }

void Deque::pushFront(double value) {
    int n = getSize();
    enqueue(value);
    for (int i = 0; i < n; i++) rotate();
}

void Deque::pushBack(double value) { enqueue(value); }
double Deque::popFront() { return dequeue(); }

double Deque::popBack() {
    for (int i = 0; i < getSize() - 1; i++) rotate();
    return dequeue();
}

double Deque::front() const { return get(0); }
double Deque::back() const { return get(getSize() - 1); }
