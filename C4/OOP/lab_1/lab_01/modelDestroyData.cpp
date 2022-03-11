#include "modelDestroyData.h"

// DONE

/*
 * Clear model
 */

void clearPoint(Point& point)
{
    point.x = 0;
    point.y = 0;
    point.z = 0;
}

void freeEdges(EdgeArr& edges)
{
    edges.edgeCount = 0;
    if (edges.edgeArr != NULL)
        free(edges.edgeArr);
}

void freePoints(PointArr& points)
{
    points.pointCount = 0;
    if (points.pointArr != NULL)
        free(points.pointArr);
}

void clearModel(Model3D& model)
{
    clearPoint(model.pivot);
    freeEdges(model.edges);
    freePoints(model.points);
}

/*
 * Projection delete section
 */

void freeCanvasPoints(CanvasPointArr& canvasPoints)
{
    canvasPoints.pointCount = 0;
    if (canvasPoints.canvasPointArr != NULL)
        free(canvasPoints.canvasPointArr);
}

void freeLines(LineArr& lines)
{
    lines.lineCount = 0;
    if (lines.lineArr == NULL)
        free(lines.lineArr);
}

void clearProjection(ModelProj& projection)
{
    freeCanvasPoints(projection.canvasPoints);
    freeLines(projection.lines);
}
