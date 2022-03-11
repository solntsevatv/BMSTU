#ifndef MEMENTO_H
#define MEMENTO_H

#include "basestate.h"

class Memento
{
public:
    Memento();
    ~Memento() = default;

    Memento(BaseState state);
    BaseState getState();

protected:
    BaseState state;
};

#endif // MEMENTO_H
