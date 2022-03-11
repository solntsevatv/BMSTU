#ifndef FACADE_H
#define FACADE_H

#include "commandcontroller.h"
#include "basecommand.h"

class Facade
{
public:
    Facade();

protected:
    CommandController commandController;
    void execute(BaseCommand baseCommand);
};

#endif // FACADE_H
