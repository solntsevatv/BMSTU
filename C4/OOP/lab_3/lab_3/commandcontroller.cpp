#include "commandcontroller.h"

CommandController::CommandController()
{

}

BaseManager &CommandController::getSceneManager()
{
    return sceneManager;
}

BaseManager &CommandController::getSelectManager()
{
    return selectManager;
}

BaseManager &CommandController::getTransformManager()
{
    return transformManager;
}

BaseManager &CommandController::getRenderManager()
{
    return renderManager;
}

BaseManager &CommandController::getStateManager()
{
    return stateManager;
}

