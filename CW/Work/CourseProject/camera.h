#ifndef CAMERA_H
#define CAMERA_H

#include "baseobject.h"
#include "mesh.h"
#include "vector3.h"

class Camera : public BaseObject
{
public:
    Camera();
    Vector3 up_ = {0, 1, 0};
    Vector3 lookDir_ = {0, 0, 1};
    Vector3 right_ = {1, 0, 0};

    Vector3 localRotation_ = {0, 0, 0};

    void rotate(Vector3 delta) override;
    void move(Vector3 delta) override;

    void localRotation(Vector3 delta);

    Vector3 formVectorToPosition(Vector3 position);
    Vector3 formVectorToPositionNormalized(Vector3 position);

    Matrix formViewMatrix();
    void pointAtMatrix(Vector3 &pos, Vector3 &target, Vector3 &up, Matrix &result);
protected:
    void scale(Vector3 koef) override;
};

#endif // CAMERA_H
