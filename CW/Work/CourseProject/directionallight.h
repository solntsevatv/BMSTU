#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "baseobject.h"
#include <QColor>

class DirectionalLight : public BaseObject
{
public:
    DirectionalLight();

    Vector3 direction;
    QColor color;
    float power = 1.0f;
};

#endif // DIRECTIONALLIGHT_H
