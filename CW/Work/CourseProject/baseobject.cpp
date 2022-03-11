#include "baseobject.h"

BaseObject::BaseObject()
{

}

void BaseObject::rotate(Vector3 delta)
{
    Matrix rotationMatrix;

    delta *= M_PI / 180;

    rotationMatrix = formRotateMatrix(delta);
    // return to (0, 0, 0)
    Vector3 oldPosition = position_;
    Vector3 toCenter = position_ * -1;

    rotation_ += delta;
    if (abs(rotation_.x_) > 360)
        rotation_.x_ = rotation_.x_ - (rotation_.x_ / 360) * 360;
    if (abs(rotation_.y_) > 360)
        rotation_.y_ = rotation_.y_ - (rotation_.y_ / 360) * 360;
    if (abs(rotation_.x_) > 360)
        rotation_.z_ = rotation_.z_ - (rotation_.z_ / 360) * 360;

    move(toCenter);
    // return to position
    move(oldPosition);
}

void BaseObject::move(Vector3 delta)
{
    position_ = position_ + delta;

    Matrix moveMatrix;
    moveMatrix = formMoveMatrix(delta);
}

void BaseObject::scale(Vector3 koef)
{
    Matrix scaleMatrix;
    scaleMatrix = formScaleMatrix(koef);
    // return to (0, 0, 0)
    scale_ *= koef;
    Vector3 oldPosition = position_;
    Vector3 toCenter = position_ * -1;
    move(toCenter);
    // scale
    // return to position
    move(oldPosition);
}

Matrix BaseObject::formMoveMatrix(Vector3 &deltaCoords)
{
    Matrix moveMatrix;
    moveMatrix.identity();
    moveMatrix.data_[0][3] = deltaCoords.x_;
    moveMatrix.data_[1][3] = deltaCoords.y_;
    moveMatrix.data_[2][3] = deltaCoords.z_;
    return moveMatrix;
}

Matrix BaseObject::formRotateMatrix(Vector3 &rotationAngles)
{
    Matrix rotationZ;
    // Rotation Z
    rotationZ.data_[0][0] = round(cosf(rotationAngles.z_) * ROUND) / ROUND;
    rotationZ.data_[0][1] = round(sinf(rotationAngles.z_) * ROUND) / ROUND;
    rotationZ.data_[1][0] = round(-sinf(rotationAngles.z_) * ROUND) / ROUND;
    rotationZ.data_[1][1] = round(cosf(rotationAngles.z_) * ROUND) / ROUND;
    rotationZ.data_[2][2] = 1;
    rotationZ.data_[3][3] = 1;

    Matrix rotationY;
    // Rotation Y
    rotationY.data_[0][0] = round(cosf(rotationAngles.y_) * ROUND) / ROUND;
    rotationY.data_[0][2] = round(sinf(rotationAngles.y_) * ROUND) / ROUND;
    rotationY.data_[1][1] = 1;
    rotationY.data_[2][0] = round(-sinf(rotationAngles.y_) * ROUND) / ROUND;
    rotationY.data_[2][2] = round(cosf(rotationAngles.y_) * ROUND) / ROUND;
    rotationY.data_[3][3] = 1;

    Matrix rotationX;
    // Rotation X
    rotationX.data_[0][0] = 1;
    rotationX.data_[1][1] = round(cosf(rotationAngles.x_) * ROUND) / ROUND;
    rotationX.data_[1][2] = round(-sinf(rotationAngles.x_) * ROUND) / ROUND;
    rotationX.data_[2][1] = round(sinf(rotationAngles.x_) * ROUND) / ROUND;
    rotationX.data_[2][2] = round(cosf(rotationAngles.x_) * ROUND) / ROUND;
    rotationX.data_[3][3] = 1;

    rotationZ = rotationZ.dot(rotationY);
    rotationZ = rotationZ.dot(rotationX);

    return rotationZ;
}

Matrix BaseObject::formScaleMatrix(Vector3 &scaleKoef)
{
    Matrix scaleMatrix;
    scaleMatrix.identity();
    scaleMatrix.data_[0][0] = scaleKoef.x_;
    scaleMatrix.data_[1][1] = scaleKoef.y_;
    scaleMatrix.data_[2][2] = scaleKoef.z_;
    return scaleMatrix;
}
