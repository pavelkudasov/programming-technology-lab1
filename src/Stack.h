#ifndef STACK_H
#define STACK_H

#include "Queue.h"

class Stack : public Queue {
public:
    Stack();
    Stack(double value);
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack() override;
    int getType() const override;
    Queue* clone() const override;
    void push(double value);
    double pop();
    double top() const;
};

#endif
