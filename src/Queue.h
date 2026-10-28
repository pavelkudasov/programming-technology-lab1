#ifndef QUEUE_H
#define QUEUE_H

#include <iosfwd>

class Queue {
private:
    struct Node {
        double value;
        Node* next;
    };

    Node* first;
    Node* last;
    int count;

protected:
    void enqueue(double value);
    double dequeue();
    void rotate();

public:
    Queue();
    Queue(double value);
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    virtual ~Queue();

    virtual int getType() const = 0;
    virtual Queue* clone() const = 0;
    int getSize() const;
    double get(int index) const;
    void set(int index, double value);
    void clear();
    friend std::ostream& operator<<(std::ostream& out, const Queue& queue);
};

#endif
