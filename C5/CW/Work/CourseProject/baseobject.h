#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#define ROUND 100000
// VERIFIED

#include "vector3.h"

class BaseObject
{
public:
    BaseObject();

    Vector3 position_ = {0, 0, 0};
    Vector3 rotation_ = {0, 0, 0};
    Vector3 scale_ = {1.0, 1.0, 1.0};

    virtual void rotate(Vector3 delta);
    virtual void move(Vector3 delta);
    virtual void scale(Vector3 koef);

protected:
    Matrix formMoveMatrix(Vector3 &deltaCoords);
    Matrix formRotateMatrix(Vector3 &rotationAnlges);
    Matrix formScaleMatrix(Vector3 &scaleKoef);
};

#endif // BASEOBJECT_H
