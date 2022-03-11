#ifndef TRANSFORMCOMMANDS_H
#define TRANSFORMCOMMANDS_H

#include "basecommand.h"

class TransformObjectCommand : public BaseCommand
{
public:
     TransformObjectCommand();
};

class TransformSelectedGroupCommand : public BaseCommand
{
public:
     TransformSelectedGroupCommand();
};

#endif // TRANSFORMCOMMANDS_H
