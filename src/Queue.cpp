#include "Queue.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Queue::Queue() : first(nullptr), last(nullptr), count(0) {
    std::cout << "Queue " << this << ": конструктор без параметров\n";
}

Queue::Queue(double value) : first(nullptr), last(nullptr), count(0) {
    enqueue(value);
    std::cout << "Queue " << this << ": конструктор с параметром\n";
}

Queue::Queue(const Queue& other) : first(nullptr), last(nullptr), count(0) {
    try {
        Node* current = other.first;
        while (current != nullptr) {
            enqueue(current->value);
            current = current->next;
        }
    } catch (...) {
        clear();
        throw;
    }
    std::cout << "Queue " << this << ": конструктор копирования\n";
}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        // Готовим копию до удаления старых данных.
        Queue* copy = other.clone();
        clear();
        first = copy->first;
        last = copy->last;
        count = copy->count;
        copy->first = nullptr;
        copy->last = nullptr;
        copy->count = 0;
        delete copy;
    }
    return *this;
}

Queue::~Queue() {
    clear();
    std::cout << "Queue " << this << ": деструктор\n";
}

void Queue::enqueue(double value) {
    if (!std::isfinite(value)) {
        throw std::invalid_argument("Нужно конечное число.");
    }
    Node* node = new Node;
    node->value = value;
    node->next = nullptr;
    if (last == nullptr) first = node;
    else last->next = node;
    last = node;
    count++;
}

double Queue::dequeue() {
    if (count == 0) throw std::runtime_error("Контейнер пуст.");
    Node* node = first;
    double value = node->value;
    first = first->next;
    delete node;
    count--;
    if (count == 0) last = nullptr;
    return value;
}

void Queue::rotate() {
    if (count < 2) return;
    // Переносим первый узел очереди в конец.
    Node* node = first;
    first = first->next;
    last->next = node;
    last = node;
    last->next = nullptr;
}

int Queue::getSize() const { return count; }

double Queue::get(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Неверный номер элемента.");
    }
    Node* current = first;
    for (int i = 0; i < index; i++) current = current->next;
    return current->value;
}

void Queue::set(int index, double value) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Неверный номер элемента.");
    }
    if (!std::isfinite(value)) {
        throw std::invalid_argument("Нужно конечное число.");
    }
    Node* current = first;
    for (int i = 0; i < index; i++) current = current->next;
    current->value = value;
}

void Queue::clear() {
    while (count > 0) dequeue();
}

std::ostream& operator<<(std::ostream& out, const Queue& queue) {
    if (queue.getType() == 1) out << "Стек";
    else if (queue.getType() == 2) out << "Дек";
    else out << "Список";
    out << ": [";
    Queue::Node* current = queue.first;
    while (current != nullptr) {
        out << current->value;
        current = current->next;
        if (current != nullptr) out << ", ";
    }
    return out << ']';
}
