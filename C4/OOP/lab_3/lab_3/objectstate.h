#ifndef OBJECTSTATE_H
#define OBJECTSTATE_H

#include "iostream"
#include "list"
#include "basestate.h"
#include "basetransform.h"
#include "baseobject.h"

class ObjectState : public BaseState
{
public:
    ObjectState();
    ~ObjectState();

    std::string getID() const;
    void setID(std::string &newName);
    BaseTransform getTransform();
    void setTransform(const BaseTransform &newTransform);
    void setVisibility(bool isVisible);
    bool getVisibility();
    std::list<BaseObject> getChildren();
    void setChildren(std::list<BaseObject> children);
    void copy(ObjectState &state);

protected:
    std::string ID;
    BaseTransform transform;
    bool visibility;
    std::list<BaseObject> children;
};

#endif // OBJECTSTATE_H
