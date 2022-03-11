#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3.h"
#include <QColor>
#include <math.h>

// NOT COMPLETE

class Triangle
{
public:
    Triangle();
    Triangle(const Triangle &triangle);
    Triangle(float points[3][3]);
    Triangle(Vector3 a, Vector3 b, Vector3 c);

    void operator= (const Triangle &triangle);

    Vector3 getPlaneIntersection(Vector3 &plane_point, Vector3 &plane_normal, Vector3 &line_start, Vector3 &line_end);
    int ClipAgainstPlane(Vector3 plane_point, Vector3 plane_normal, Triangle &in_triangle, Triangle &out_triangle_1, Triangle &out_triangle_2, Vector3 tri_normal);

    Vector3 getNormal();
    Vector3 vertices[3];
    QColor color;
};

#endif // TRIANGLE_H
