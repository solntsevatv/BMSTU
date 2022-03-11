#include "baseobject.h"

BaseObject::BaseObject()
{

}

BaseObject::~BaseObject()
{

}

void BaseObject::doTransform(BaseTransform transform)
{

}

BaseObject BaseObject::copy()
{
    BaseObject copyObject = BaseObject();
    copyObject.state.copy(state);
    return copyObject;
}

void BaseObject::addChild(BaseObject child)
{
    auto children = state.getChildren();
    children.push_front(child);
    state.setChildren(children);
}

void BaseObject::removeChild(ObjectID ID) // нужны умные указатели
{
    auto iter = begin();
    while(iter != end())
    {
        if (iter->state.getID() == ID)
        {
            state.getChildren().erase(iter);
            break;
        }
        iter++;
    }
}

bool BaseObject::isComposite()
{
    return state.getChildren().size() != 0;
}

bool BaseObject::isVisible()
{
    return state.getVisibility();
}

void BaseObject::setVisibility(bool visible)
{
    state.setVisibility(visible);
}

Memento BaseObject::saveState()
{
    return Memento(state);
}

void BaseObject::restoreState(Memento restState)
{
    state.copy(restState.getState());
}

std::list<BaseObject>::iterator BaseObject::begin()
{
    return state.getChildren().begin();
}

std::list<BaseObject>::iterator BaseObject::end()
{
    return state.getChildren().end();
}

void BaseObject::accept(BaseObjectVisitor) // Доделать аксепт
{

}


