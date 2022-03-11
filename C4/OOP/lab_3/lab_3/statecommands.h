#ifndef STATECOMMANDS_H
#define STATECOMMANDS_H

#include "basecommand.h"

class UndoCommand : public BaseCommand
{
public:
    UndoCommand();
};

class RedoCommand : public BaseCommand
{
public:
    RedoCommand();
};

#endif // STATECOMMANDS_H
