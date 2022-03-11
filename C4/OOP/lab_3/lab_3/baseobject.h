#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "objectstate.h"
#include "basetransform.h"
#include "objectid.h"
#include "memento.h"
#include "baseobjectvisitor.h"

#include <list>
#include <iterator>

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    virtual void doTransform(BaseTransform transform);
    virtual BaseObject copy();
    virtual void addChild(BaseObject child);
    virtual void removeChild(ObjectID ID);
    virtual bool isComposite();
    virtual bool isVisible();
    virtual void setVisibility(bool visible);
    virtual Memento saveState();
    virtual void restoreState(Memento restState);
    virtual std::list<BaseObject>::iterator begin();
    virtual std::list<BaseObject>::iterator end();
    virtual void accept(BaseObjectVisitor);

protected:
    ObjectState state; // нужно сделать деструктор для списка детей через removeChild
};

#endif // BASEOBJECT_H
