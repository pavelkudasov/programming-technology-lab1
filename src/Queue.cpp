#include "Queue.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

int Queue::nextId = 0;

Queue::Queue()
    : data(new double[4]), capacity(4), front(0), count(0), id(++nextId) {
    std::cout << "Queue #" << id << ": конструктор без параметров\n";
}

Queue::Queue(int initialCapacity)
    : data(nullptr), capacity(initialCapacity), front(0), count(0), id(++nextId) {
    if (capacity < 1 || capacity > MAX_CAPACITY) {
        throw std::invalid_argument("Вместимость должна быть от 1 до 100000.");
    }

    data = new double[capacity];
    std::cout << "Queue #" << id << ": конструктор с параметрами\n";
}

Queue::Queue(const Queue& other)
    : data(new double[other.capacity]), capacity(other.capacity),
      front(0), count(other.count), id(++nextId) {
    // У копии свой массив. Копируем числа, а не адрес старого массива.
    for (int i = 0; i < count; i++) {
        data[i] = other.get(i);
    }

    std::cout << "Queue #" << id << ": конструктор копирования из #"
              << other.id << '\n';
}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        // Сначала создаём копию, только затем освобождаем старый массив.
        double* copy = new double[other.capacity];
        for (int i = 0; i < other.count; i++) {
            copy[i] = other.get(i);
        }

        delete[] data;
        data = copy;
        capacity = other.capacity;
        count = other.count;
        front = 0;
    }
    return *this;
}

Queue::~Queue() {
    std::cout << "Queue #" << id << ": деструктор\n";
    delete[] data;
}

int Queue::size() const { return count; }
int Queue::getCapacity() const { return capacity; }
int Queue::getId() const { return id; }
bool Queue::isEmpty() const { return count == 0; }

double Queue::get(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Номер элемента находится вне диапазона.");
    }
    // Очередь может начинаться не с нулевой ячейки массива.
    return data[(front + index) % capacity];
}

void Queue::checkValue(double value) {
    if (!std::isfinite(value)) {
        throw std::invalid_argument("Число должно быть конечным.");
    }
}

void Queue::set(int index, double value) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Номер изменяемого элемента вне диапазона.");
    }
    checkValue(value);
    data[(front + index) % capacity] = value;
}

void Queue::setCapacity(int newCapacity) {
    if (newCapacity < 1 || newCapacity > MAX_CAPACITY || newCapacity < count) {
        throw std::invalid_argument(
            "Вместимость: от 1 до 100000 и не меньше числа элементов.");
    }

    double* copy = new double[newCapacity];
    for (int i = 0; i < count; i++) {
        copy[i] = get(i);
    }

    delete[] data;
    data = copy;
    capacity = newCapacity;
    front = 0;
}

void Queue::prepareAdd() {
    if (count < capacity) return;

    if (capacity == MAX_CAPACITY) {
        throw std::runtime_error("Достигнут предел: 100000 элементов.");
    }

    int newCapacity = capacity * 2;
    if (newCapacity > MAX_CAPACITY) newCapacity = MAX_CAPACITY;
    setCapacity(newCapacity);
}

void Queue::enqueue(double value) {
    checkValue(value);
    prepareAdd();

    // Новое число ставим после последнего элемента очереди.
    data[(front + count) % capacity] = value;
    count++;
}

double Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Нельзя извлечь элемент: очередь пуста.");
    }

    double value = data[front];
    front = (front + 1) % capacity;
    count--;
    return value;
}

void Queue::rotate() {
    // Извлекаем первое число и переносим его в конец.
    double value = dequeue();
    enqueue(value);
}

void Queue::print(std::ostream& out) const {
    out << type() << " #" << id << ", элементов: " << count
        << ", вместимость: " << capacity << ": [";

    for (int i = 0; i < count; i++) {
        if (i != 0) out << ", ";
        out << get(i);
    }
    out << ']';
}

std::ostream& operator<<(std::ostream& out, const Queue& queue) {
    queue.print(out);
    return out;
}
