#include "transfrom3d.h"

Transfrom3D::Transfrom3D()
{

}

Vector Transfrom3D::getMove()
{
    return move;
}

Vector Transfrom3D::getRotate()
{
    return rotate;
}

Vector Transfrom3D::getScale()
{
    return scale;
}

void Transfrom3D::setMove(Vector &newMove)
{
    move = newMove;
}

void Transfrom3D::setRotate(Vector &newRotate)
{
    rotate = newRotate;
}

void Transfrom3D::setScale(Vector &newScale)
{
    scale = newScale;
}
