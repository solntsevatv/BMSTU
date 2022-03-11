#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "commandcontroller.h"

class BaseCommand
{
public:
    BaseCommand();
    virtual ~BaseCommand() = 0;

    virtual void execute(CommandController commandController);
};

#endif // BASECOMMAND_H
