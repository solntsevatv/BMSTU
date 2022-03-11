#ifndef OBJECTID_H
#define OBJECTID_H

#include "iostream"

class ObjectID
{
public:
    ObjectID();
    ~ObjectID() = default;

    std::string getID();

protected:
    std::string objectID;
};

#endif // OBJECTID_H
