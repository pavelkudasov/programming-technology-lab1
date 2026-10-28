#ifndef LIST_H
#define LIST_H

#include "Queue.h"

class List : public Queue {
public:
    List();
    List(double value);
    List(const List& other);
    List& operator=(const List& other);
    ~List() override;
    int getType() const override;
    Queue* clone() const override;
    void insert(int index, double value);
    double remove(int index);
};

#endif
