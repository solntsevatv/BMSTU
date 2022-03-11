#ifndef SELECTIONCOMMANDS_H
#define SELECTIONCOMMANDS_H

#include "basecommand.h"

class ChangeSelectionCommand : public BaseCommand
{
public:
    ChangeSelectionCommand();
};

class SelectAllCommand : public BaseCommand
{
public:
    SelectAllCommand();
};

class ClearAllCommand : public BaseCommand
{
public:
    ClearAllCommand();
};

#endif // SELECTIONCOMMANDS_H
