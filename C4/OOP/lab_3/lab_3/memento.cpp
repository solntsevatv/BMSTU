#include "memento.h"

Memento::Memento()
{

}

Memento::Memento(BaseState newState)
{
    state = newState;
}

BaseState Memento::getState()
{
    return state;
}
