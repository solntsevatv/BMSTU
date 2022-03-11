#ifndef CAMERACOMMANDS_H
#define CAMERACOMMANDS_H

#include "basecommand.h"

class GoToActiveCameraCommand : public BaseCommand
{
public:
    GoToActiveCameraCommand();
};

class LookAtSelectedCommand : public BaseCommand
{
public:
    LookAtSelectedCommand();
};


class MakeCameraActiveCommand : public BaseCommand
{
public:
    MakeCameraActiveCommand();
};


#endif // CAMERACOMMANDS_H
