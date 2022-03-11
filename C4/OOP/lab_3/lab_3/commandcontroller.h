#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include "basemanager.h"

class CommandController
{
public:
    CommandController();
    ~CommandController() = default;

protected:
    BaseManager sceneManager;
    BaseManager selectManager;
    BaseManager transformManager;
    BaseManager renderManager;
    BaseManager stateManager;

public:
    BaseManager& getSceneManager();
    BaseManager& getSelectManager();
    BaseManager& getTransformManager();
    BaseManager& getRenderManager();
    BaseManager& getStateManager();
};

#endif // COMMANDCONTROLLER_H
