#include "facade.h"

Facade::Facade()
{

}

void Facade::execute(BaseCommand baseCommand)
{
    baseCommand.execute(commandController);
}
