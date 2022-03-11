#ifndef TRANSFROM3D_H
#define TRANSFROM3D_H

#include "basetransform.h"

class Vector
{
public:
    Vector() = default;

public:
    double getX(){return x;};
    double getY(){return y;};
    double getZ(){return z;};

protected:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

class Transfrom3D : public BaseTransform
{
public:
    Transfrom3D();

    Vector getMove();
    Vector getRotate();
    Vector getScale();

    void setMove(Vector &newMove);
    void setRotate(Vector &newRotate);
    void setScale(Vector &newScale);

protected:
    Vector move;
    Vector rotate;
    Vector scale;

};

#endif // TRANSFROM3D_H
