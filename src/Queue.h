#ifndef QUEUE_H
#define QUEUE_H

#include <iosfwd>

// Абстрактная очередь. Наследники выполняют свои операции через FIFO.
class Queue {
public:
    static const int MAX_CAPACITY = 100000;
    Queue();
    explicit Queue(int capacity);
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    virtual ~Queue();
    virtual const char* type() const = 0;
    virtual Queue* clone() const = 0;
    int size() const;
    int getCapacity() const;
    int getId() const;
    bool isEmpty() const;
    double get(int index) const;
    void set(int index, double value);
    void setCapacity(int newCapacity);
    virtual void print(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const Queue& queue);

protected:
    void enqueue(double value);
    double dequeue();
    void rotate();
    void prepareAdd();
    static void checkValue(double value);

private:
    double* data;
    int capacity;
    int front;
    int count;
    int id;
    static int nextId;
};

#endif
