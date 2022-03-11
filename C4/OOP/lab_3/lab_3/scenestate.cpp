#include "scenestate.h"

SceneState::SceneState()
{

}

void SceneState::setID(std::string &newID)
{
    ID = newID;
}

std::string &SceneState::getID()
{
    return ID;
}

void SceneState::setObjectList(std::list<BaseObject> &newObjects)
{
    objects.clear();
    objects = newObjects;
}

std::list<BaseObject> &SceneState::getObjectList()
{
    return objects;
}

void SceneState::copy(SceneState &state)
{
    setID(state.getID());
    setObjectList(state.getObjectList());
}
