#include "objectstate.h"

ObjectState::ObjectState()
{

}

ObjectState::~ObjectState()
{
    children.clear();
}

std::string ObjectState::getID() const
{
    return ID;
}

void ObjectState::setID(std::string &newID)
{
    ID = newID;
}

BaseTransform ObjectState::getTransform()
{
    return transform;
}

void ObjectState::setTransform(const BaseTransform &newTransform)
{
    transform = newTransform;
}

void ObjectState::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

bool ObjectState::getVisibility()
{
    return visibility;
}

std::list<BaseObject> ObjectState::getChildren()
{
    return children;
}

void ObjectState::setChildren(std::list<BaseObject> newChildren)
{
    children.clear();
    children = newChildren;
}

void ObjectState::copy(ObjectState &state)
{
    setID(state.ID);
    setChildren(state.children);
    setVisibility(state.visibility);
    setTransform(state.transform);
}
