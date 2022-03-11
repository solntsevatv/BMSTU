#include "scene.h"

Scene::Scene()
{

}

void Scene::addObject(BaseObject &object)
{
    auto objList = state.getObjectList();
    objList.push_front(object);
    state.setObjectList(objList);
}

void Scene::removeObject(std::string &ID)
{

}

std::list<BaseObject>::iterator Scene::begin()
{
    return state.getObjectList().begin();
}

std::list<BaseObject>::iterator Scene::end()
{
    return state.getObjectList().end();
}

void Scene::accept(BaseObjectVisitor)
{

}
