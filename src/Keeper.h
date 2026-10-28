#ifndef KEEPER_H
#define KEEPER_H

#include "Queue.h"

class Keeper {
private:
    Queue** objects;
    int count;

public:
    Keeper();
    Keeper(const Queue& object);
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();

    int getSize() const;
    Queue& get(int index);
    void add(const Queue& object);
    void remove(int index);
    void clear();
    void save(const char* filename) const;
    void load(const char* filename);
};

#endif
