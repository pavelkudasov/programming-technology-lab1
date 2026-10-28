#ifndef DEQUE_H
#define DEQUE_H

#include "Queue.h"

class Deque : public Queue {
public:
    Deque();
    Deque(double value);
    Deque(const Deque& other);
    Deque& operator=(const Deque& other);
    ~Deque() override;
    int getType() const override;
    Queue* clone() const override;
    void pushFront(double value);
    void pushBack(double value);
    double popFront();
    double popBack();
    double front() const;
    double back() const;
};

#endif
