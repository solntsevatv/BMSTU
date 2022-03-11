#ifndef MODEL_H
#define MODEL_H

#include "head.h"
#include <fstream>

struct Point
{
    float x;
    float y;
    float z;
};

struct PointArr
{
    int pointCount;
    Point *pointArr;
};

struct Edge
{
    int startIndex;
    int endIndex;
};

struct EdgeArr
{
    int edgeCount;
    Edge *edgeArr;
};

struct Model3D
{
    Point pivot;
    EdgeArr edges;
    PointArr points;
};

struct CanvasPoint
{
    int x;
    int y;
};

struct Line
{
    int start;
    int end;
};

struct LineArr
{
    int lineCount;
    Line *lineArr;
};

struct CanvasPointArr
{
    int pointCount;
    CanvasPoint *canvasPointArr;
};

struct ModelProj
{
    LineArr lines;
    CanvasPointArr canvasPoints;
};

Status modelCheck(const Model3D& model);
Status pointsCheck(const PointArr& points);

#endif // MODEL_H
