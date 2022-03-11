#include "mesh.h"
#include "math.h"
#include <QDebug>
#define EPS = 0.0001

Mesh::Mesh()
{
    tris.clear();
}

void Mesh::rotate(Vector3 delta)
{
    Matrix rotationMatrix;
    rotationMatrix = formRotateMatrix(delta);
    // return to (0, 0, 0)
    Vector3 oldPosition = position_;
    Vector3 toCenter = position_ * -1;

    rotation_ += delta;
    if (rotation_.x_ >= (2 * M_PI))
        rotation_.x_ = rotation_.x_ - (2 * M_PI);
    if (rotation_.y_ >= (2 * M_PI))
        rotation_.y_ = rotation_.y_ - (2 * M_PI);
    if (rotation_.z_ >= (2 * M_PI))
        rotation_.z_ = rotation_.z_ - (2 * M_PI);
    if (rotation_.x_ <= -(2 * M_PI))
        rotation_.x_ = rotation_.x_ + (2 * M_PI);
    if (rotation_.y_ <= -(2 * M_PI))
        rotation_.y_ = rotation_.y_ + (2 * M_PI);
    if (rotation_.z_ <= -(2 * M_PI))
        rotation_.z_ = rotation_.z_ + (2 * M_PI);


    move(toCenter);
    // rotate
    for (auto &tri : tris)
    {
        for (int i = 0; i < 3; i++)
        {
            tri.vertices[i].vdot(rotationMatrix);
        }
    }
    // return to position
    move(oldPosition);
}

void Mesh::move(Vector3 delta)
{
    position_ = position_ + delta;

    Matrix moveMatrix;
    moveMatrix = formMoveMatrix(delta);
    for (auto &tri : tris)
    {
        for (int i = 0; i < 3; i++)
        {
            tri.vertices[i].vdot(moveMatrix);
        }
    }
}

void Mesh::scale(Vector3 koef)
{
    Matrix scaleMatrix;
    scaleMatrix = formScaleMatrix(koef);
    scale_ *= koef;
    // return to (0, 0, 0)
    Vector3 oldPosition = position_;
    Vector3 toCenter = position_ * -1;
    move(toCenter);
    // rotate
    for (auto &tri : tris)
    {
        for (int i = 0; i < 3; i++)
        {
            tri.vertices[i].vdot(scaleMatrix);
        }
    }
    // return to position
    move(oldPosition);
}

void Mesh::clearValues()
{
    position_ = {0, 0, 0};
    rotation_ = {0, 0, 0};
    scale_ = {1.0, 1.0, 1.0};
    tris.clear();
}
