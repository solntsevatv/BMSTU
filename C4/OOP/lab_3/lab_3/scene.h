#ifndef SCENE_H
#define SCENE_H

#include "scenestate.h"
#include "memento.h"
#include "baseobject.h"
#include "baseobjectvisitor.h"

class Scene
{
public:
    Scene();
    ~Scene() = default;

    void addObject(BaseObject &object);
    void removeObject(std::string &ID);
    Memento &saveState();
    void restoreState(Memento &restState);
    virtual std::list<BaseObject>::iterator begin();
    virtual std::list<BaseObject>::iterator end();
    virtual void accept(BaseObjectVisitor);

protected:
    SceneState state;
};

#endif // SCENE_H
