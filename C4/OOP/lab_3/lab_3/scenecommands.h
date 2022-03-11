#ifndef SCENECOMMANDS_H
#define SCENECOMMANDS_H

#include "basecommand.h"

class SceneCreateCommand : public BaseCommand
{
public:
    SceneCreateCommand();
};

class SceneDeleteCommand : public BaseCommand
{
public:
    SceneDeleteCommand();
};

class SceneImportCommand : public BaseCommand
{
public:
    SceneImportCommand();
};

class SceneExportCommand : public BaseCommand
{
public:
    SceneExportCommand();
};

class SceneSaveCommand : public BaseCommand
{
public:
    SceneSaveCommand();
};

class SceneLoadCommand : public BaseCommand
{
public:
    SceneLoadCommand();
};

#endif // SCENECOMMANDS_H
