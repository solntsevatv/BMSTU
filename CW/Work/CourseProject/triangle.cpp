#include "triangle.h"
#include "QDebug"

Triangle::Triangle()
{

}

Triangle::Triangle(const Triangle &triangle)
{
    for (int i = 0; i < 3; i++)
    {
        vertices[i] = triangle.vertices[i];
    }
}

Triangle::Triangle(float points[3][3])
{
    vertices[0].copy(points[0]);
    vertices[1].copy(points[1]);
    vertices[2].copy(points[2]);
}

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c)
{
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
}

void Triangle::operator=(const Triangle &triangle)
{
    vertices[0] = triangle.vertices[0];
    vertices[1] = triangle.vertices[1];
    vertices[2] = triangle.vertices[2];
    color = triangle.color;
}

Vector3 Triangle::getPlaneIntersection(Vector3 &plane_point, Vector3 &plane_normal, Vector3 &line_start, Vector3 &line_end)
{
    plane_normal = plane_normal.normalized();
    float plane_d = -plane_normal.scalar(plane_point);
    float ad = line_start.scalar(plane_normal);
    float bd = line_end.scalar(plane_normal);
    float t = (-plane_d - ad) / (bd - ad);
    Vector3 lineStartToEnd = line_end - line_start;
    Vector3 lineToIntersect = lineStartToEnd * t;
    return line_start + lineToIntersect;
}

int Triangle::ClipAgainstPlane(Vector3 plane_point, Vector3 plane_normal, Triangle &in_triangle, Triangle &out_triangle_1, Triangle &out_triangle_2, Vector3 tri_normal)
{
    plane_normal = plane_normal.normalized();
    tri_normal.normalize();
    auto dist = [&](Vector3 p)
    {
        return (plane_normal.x_ * p.x_ + plane_normal.y_ * p.y_ + plane_normal.z_ * p.z_ - plane_normal.scalar(plane_point));
    };

    Vector3* inside_points[3];
    int nInsidePointCount = 0;
    Vector3* outside_points[3];
    int nOutsidePointCount = 0;

    float d0 = dist(in_triangle.vertices[0]);
    float d1 = dist(in_triangle.vertices[1]);
    float d2 = dist(in_triangle.vertices[2]);

    if (d0 >= 0)
        inside_points[nInsidePointCount++] = &in_triangle.vertices[0];
    else
        outside_points[nOutsidePointCount++] = &in_triangle.vertices[0];

    if (d1 >= 0)
        inside_points[nInsidePointCount++] = &in_triangle.vertices[1];
    else
        outside_points[nOutsidePointCount++] = &in_triangle.vertices[1];

    if (d2 >= 0)
        inside_points[nInsidePointCount++] = &in_triangle.vertices[2];
    else
        outside_points[nOutsidePointCount++] = &in_triangle.vertices[2];

    if (nInsidePointCount == 0)
        return 0;

    if (nInsidePointCount == 3)
    {
        out_triangle_1 = in_triangle;

        if (out_triangle_1.getNormal().normalized().scalar(tri_normal) < 0)
        {
            Vector3 temp = out_triangle_1.vertices[2];
            out_triangle_1.vertices[2] = out_triangle_1.vertices[1];
            out_triangle_1.vertices[1] = temp;
        }
        return 1;
    }

    if (nInsidePointCount == 1 && nOutsidePointCount == 2)
    {
        out_triangle_1 = in_triangle;
        out_triangle_1.vertices[0] = *inside_points[0];
        out_triangle_1.vertices[1] = getPlaneIntersection(plane_point, plane_normal, *inside_points[0], *outside_points[0]);
        out_triangle_1.vertices[2] = getPlaneIntersection(plane_point, plane_normal, *inside_points[0], *outside_points[1]);

        if (out_triangle_1.getNormal().normalized().scalar(tri_normal) < 0)
        {
            Vector3 temp = out_triangle_1.vertices[2];
            out_triangle_1.vertices[2] = out_triangle_1.vertices[1];
            out_triangle_1.vertices[1] = temp;
        }

        return 1;
    }

    if (nInsidePointCount == 2 && nOutsidePointCount == 1)
    {
        out_triangle_1 = in_triangle;
        out_triangle_2 = in_triangle;

        out_triangle_1.vertices[0] = *inside_points[0];
        out_triangle_1.vertices[1] = *inside_points[1];
        out_triangle_1.vertices[2] = getPlaneIntersection(plane_point, plane_normal, *inside_points[0], *outside_points[0]);

        if (out_triangle_1.getNormal().normalized().scalar(tri_normal) < 0)
        {
            Vector3 temp = out_triangle_1.vertices[2];
            out_triangle_1.vertices[2] = out_triangle_1.vertices[1];
            out_triangle_1.vertices[1] = temp;
        }

        out_triangle_2.vertices[0] = *inside_points[1];
        out_triangle_2.vertices[1] = out_triangle_1.vertices[2];
        if (abs(out_triangle_2.vertices[1].x_ - out_triangle_2.vertices[0].x_) < 0.0001 &&\
            abs(out_triangle_2.vertices[1].y_ - out_triangle_2.vertices[0].y_) < 0.0001 &&\
            abs(out_triangle_2.vertices[1].z_ - out_triangle_2.vertices[0].z_) < 0.0001)
            out_triangle_2.vertices[1] = out_triangle_1.vertices[1];
        out_triangle_2.vertices[2] = getPlaneIntersection(plane_point, plane_normal, *inside_points[1], *outside_points[0]);

        if (out_triangle_2.getNormal().normalized().scalar(tri_normal) < 0)
        {
            Vector3 temp = out_triangle_2.vertices[2];
            out_triangle_2.vertices[2] = out_triangle_2.vertices[1];
            out_triangle_2.vertices[1] = temp;
        }

        return 2;
    }
    return 0;
}

Vector3 Triangle::getNormal()
{
    Vector3 normal;

    Vector3 a = vertices[1] - vertices[0];
    Vector3 b = vertices[2] - vertices[0];

    normal.x_ = a.y_ * b.z_ - a.z_ * b.y_;
    normal.y_ = a.z_ * b.x_ - a.x_ * b.z_;
    normal.z_ = a.x_ * b.y_ - a.y_ * b.x_;

    normal.normalize();

    return normal;
}
