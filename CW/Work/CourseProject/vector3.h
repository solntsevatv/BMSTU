#ifndef VECTOR3_H
#define VECTOR3_H

#include "math.h"
#include "matrix.h"

// NOT TESTED

class Vector3
{
public:
    Vector3();
    Vector3(const Vector3 &vector);
    Vector3(float x, float y, float z);
    Vector3(float vector[3]);

    float magnitude();
    float distance(Vector3 point);
    Vector3 normalized();
    void normalize();

    void vdot(Matrix &matrix);
    void vdot(Matrix &matrix, Vector3 &result);

    Vector3 operator+ (Vector3 &vector);
    Vector3 operator- (Vector3 &vector);
    Vector3 operator* (Vector3 &vector);
    Vector3 operator/ (Vector3 &vector);

    Vector3 operator+ (float num);
    Vector3 operator- (float num);
    Vector3 operator* (float num);
    Vector3 operator/ (float num);

    bool operator== (const Vector3 &vector);

    void operator= (const Vector3 &vector);

    void operator+= (Vector3 vector);
    void operator-= (Vector3 vector);
    void operator*= (Vector3 vector);
    void operator/= (Vector3 vector);

    void operator+= (float num);
    void operator-= (float num);
    void operator*= (float num);
    void operator/= (float num);

    void copy(float vector[3]);
    void copy(Vector3 vector);

    float scalar(Vector3 vector);
    Vector3 vector(Vector3 vector);

    float x_;
    float y_;
    float z_;
};

#endif // VECTOR3_H
