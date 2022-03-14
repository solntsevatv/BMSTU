#include "vector3.h"
#include <QDebug>

Vector3::Vector3()
{

}

Vector3::Vector3(const Vector3 &vector)
{
    x_ = vector.x_;
    y_ = vector.y_;
    z_ = vector.z_;
}

Vector3::Vector3(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

Vector3::Vector3(float vector[3])
{
    x_ = vector[0];
    y_ = vector[1];
    z_ = vector[2];
}

float Vector3::magnitude()
{
    return sqrtf(x_*x_ + y_*y_ + z_*z_);
}

float Vector3::distance(Vector3 point)
{
    Vector3 vector;
    vector.x_ = point.x_ - x_;
    vector.y_ = point.y_ - y_;
    vector.z_ = point.z_ - z_;
    return vector.magnitude();
}

Vector3 Vector3::normalized()
{
    Vector3 vector(*this);
    return vector / vector.magnitude();
}

void Vector3::normalize()
{
    x_ /= magnitude();
    y_ /= magnitude();
    z_ /= magnitude();
}

Vector3 Vector3::operator+(Vector3 &vector)
{
    Vector3 newVector;
    newVector.x_ = x_ + vector.x_;
    newVector.y_ = y_ + vector.y_;
    newVector.z_ = z_ + vector.z_;
    return newVector;
}

Vector3 Vector3::operator-(Vector3 &vector)
{
    Vector3 newVector;
    newVector.x_ = x_ - vector.x_;
    newVector.y_ = y_ - vector.y_;
    newVector.z_ = z_ - vector.z_;
    return newVector;
}

Vector3 Vector3::operator*(Vector3 &vector)
{
    Vector3 newVector;
    newVector.x_ = x_ * vector.x_;
    newVector.y_ = y_ * vector.y_;
    newVector.z_ = z_ * vector.z_;
    return newVector;
}

Vector3 Vector3::operator/(Vector3 &vector)
{
    Vector3 newVector;
    if (vector.x_ != 0 && vector.y_ != 0 && vector.z_ != 0)
    {
        newVector.x_ = x_ / vector.x_;
        newVector.y_ = y_ / vector.y_;
        newVector.z_ = z_ / vector.z_;
    }
    return newVector;
}

bool Vector3::operator==(const Vector3 &vector)
{
    if (int(this->x_) == int(vector.x_) && int(this->y_) == int(vector.y_) && int(this->z_) == int(vector.z_))
        return true;
    return false;
}

Vector3 Vector3::operator+(float num)
{
    Vector3 newVector;
    newVector.x_ = x_ + num;
    newVector.y_ = y_ + num;
    newVector.z_ = z_ + num;
    return newVector;
}

Vector3 Vector3::operator-(float num)
{
    Vector3 newVector;
    newVector.x_ = x_ - num;
    newVector.y_ = y_ - num;
    newVector.z_ = z_ - num;
    return newVector;
}

Vector3 Vector3::operator*(float num)
{
    Vector3 newVector;
    newVector.x_ = x_ * num;
    newVector.y_ = y_ * num;
    newVector.z_ = z_ * num;
    return newVector;
}

Vector3 Vector3::operator/(float num)
{
    Vector3 newVector;
    if (num != 0)
    {
        newVector.x_ = x_ / num;
        newVector.y_ = y_ / num;
        newVector.z_ = z_ / num;
    }
    return newVector;
}

void Vector3::operator=(const Vector3 &vector)
{
    x_ = vector.x_;
    y_ = vector.y_;
    z_ = vector.z_;
}

void Vector3::operator+=(Vector3 vector)
{
    x_ += vector.x_;
    y_ += vector.y_;
    z_ += vector.z_;
}

void Vector3::operator-=(Vector3 vector)
{
    x_ -= vector.x_;
    y_ -= vector.y_;
    z_ -= vector.z_;
}

void Vector3::operator*=(Vector3 vector)
{
    x_ *= vector.x_;
    y_ *= vector.y_;
    z_ *= vector.z_;
}

void Vector3::operator/=(Vector3 vector)
{
    if (vector.x_ != 0)
        x_ /= vector.x_;
    if (vector.y_ != 0)
        y_ /= vector.y_;
    if (vector.z_ != 0)
        z_ /= vector.z_;
}

void Vector3::operator+=(float num)
{
    x_ += num;
    y_ += num;
    z_ += num;
}

void Vector3::operator-=(float num)
{
    x_ -= num;
    y_ -= num;
    z_ -= num;
}

void Vector3::operator*=(float num)
{
    x_ *= num;
    y_ *= num;
    z_ *= num;
}

void Vector3::operator/=(float num)
{
    if (num != 0)
    {
        x_ /= num;
        y_ /= num;
        z_ /= num;
    }
}

void Vector3::copy(float vector[3])
{
    x_ = vector[0];
    y_ = vector[1];
    z_ = vector[2];
}

void Vector3::copy(Vector3 vector)
{
    x_ = vector.x_;
    y_ = vector.y_;
    z_ = vector.z_;
}

float Vector3::scalar(Vector3 vector)
{
    return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
}

Vector3 Vector3::vector(Vector3 vector)
{
    Matrix matrix;
    Vector3 result;
    result.x_ = matrix.determinant_2x2(y_, z_, vector.y_, vector.z_);
    result.y_ = -matrix.determinant_2x2(x_, z_, vector.x_, vector.z_);
    result.z_ = matrix.determinant_2x2(x_, y_, vector.x_, vector.y_);
    return result;
}

void Vector3::vdot(Matrix &matrix)
{
    Vector3 result;
    result.x_ = 0;
    result.y_ = 0;
    result.z_ = 0;
    float w = 0;
    for (int i = 0; i < 4; i++)
    {
        result.x_ = x_ * matrix.data_[0][0] + y_ * matrix.data_[0][1] + z_ * matrix.data_[0][2] + matrix.data_[0][3];
        result.y_ = x_ * matrix.data_[1][0] + y_ * matrix.data_[1][1] + z_ * matrix.data_[1][2] + matrix.data_[1][3];
        result.z_ = x_ * matrix.data_[2][0] + y_ * matrix.data_[2][1] + z_ * matrix.data_[2][2] + matrix.data_[2][3];
        w = x_ * matrix.data_[3][0] + y_ * matrix.data_[3][1] + z_ * matrix.data_[3][2] + matrix.data_[3][3];

        if (abs(w) > 0.00001)
        {
            result.x_ /= w;
            result.y_ /= w;
            result.z_ /= w;
        }
    }
    x_ = result.x_;
    y_ = result.y_;
    z_ = result.z_;
}

void Vector3::vdot(Matrix &matrix, Vector3 &result)
{
    result.x_ = 0;
    result.y_ = 0;
    result.z_ = 0;
    float w = 0;
    result.x_ = x_ * matrix.data_[0][0] + y_ * matrix.data_[1][0] + z_ * matrix.data_[2][0] + matrix.data_[3][0];
    result.y_ = x_ * matrix.data_[0][1] + y_ * matrix.data_[1][1] + z_ * matrix.data_[2][1] + matrix.data_[3][1];
    result.z_ = x_ * matrix.data_[0][2] + y_ * matrix.data_[1][2] + z_ * matrix.data_[2][2] + matrix.data_[3][2];
    w = x_ * matrix.data_[0][3] + y_ * matrix.data_[1][3] + z_ * matrix.data_[2][3] + matrix.data_[3][3];
    if (abs(w) > 0.00001)
    {
        result.x_ /= w;
        result.y_ /= w;
        result.z_ /= w;
    }
}


