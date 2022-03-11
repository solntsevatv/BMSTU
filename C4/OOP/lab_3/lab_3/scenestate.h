#ifndef SCENESTATE_H
#define SCENESTATE_H

#include "basestate.h"
#include "baseobject.h"
#include "iostream"

class SceneState : public BaseState
{
public:
    SceneState();
    ~SceneState() = default;

    void setID(std::string &newID);
    std::string &getID();

    void setObjectList(std::list<BaseObject> &newObjects);
    std::list<BaseObject> &getObjectList();

    void copy(SceneState &state);

protected:
    std::string ID;
    std::list<BaseObject> objects;
};

#endif // SCENESTATE_H
