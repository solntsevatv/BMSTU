#ifndef OBJECTCOMMANDS_H
#define OBJECTCOMMANDS_H

#include "basecommand.h"

class AddObjectCommand : public BaseCommand
{
public:
    AddObjectCommand();
};

class RemoveObjectCommand : public BaseCommand
{
public:
    RemoveObjectCommand();
};

#endif // OBJECTCOMMANDS_H
