#include "modelTransformFuncs.h"

/*
 * Projection section
 */

// Project points

void projectPoint(CanvasPoint& projPoint, const Point& origPoint)
{
    projPoint.x = int(origPoint.x);
    projPoint.y = int(origPoint.y);
}

Status allocateCanvasPointArr(CanvasPointArr& canvasPoints, int count)
{
    Status statusCode = copyCount(canvasPoints.pointCount, count);
    if (statusCode != success)
        return statusCode;
    canvasPoints.canvasPointArr = (CanvasPoint *)malloc(sizeof(CanvasPoint) * count);
    if (canvasPoints.canvasPointArr == NULL)
        return err_memory_allocation_error;
    return success;
}

Status projectPoints(CanvasPointArr& canvasPoints, const PointArr& points)
{
    if (points.pointArr == NULL || points.pointCount == 0)
        return err_model_empty;
    freeCanvasPoints(canvasPoints);
    Status statusCode = allocateCanvasPointArr(canvasPoints, points.pointCount);
    if (statusCode != success)
        return statusCode;
    for (int i = 0; i < canvasPoints.pointCount; i++)
        projectPoint(canvasPoints.canvasPointArr[i], points.pointArr[i]);
    return statusCode;
}

// Project edges

void projectEdge(Line& projLine, Edge modelEdge)
{
    projLine.start = modelEdge.startIndex;
    projLine.end = modelEdge.endIndex;
}

Status allocateLines(LineArr& lines, int edgeCount)
{
    Status statusCode = copyCount(lines.lineCount, edgeCount);
    if (statusCode != success)
        return statusCode;
    lines.lineArr = (Line *)malloc(sizeof(Line) * edgeCount);
    if (lines.lineArr == NULL)
        return err_memory_allocation_error;
    return statusCode;
}

Status projectEdges(LineArr& lines, const EdgeArr& edges)
{
    if (edges.edgeCount == NULL || edges.edgeCount == 0)
        return err_model_empty;
    freeLines(lines);
    Status statusCode = allocateLines(lines, edges.edgeCount);
    if (statusCode != success)
        return statusCode;
    for (int i = 0; i < lines.lineCount; i++)
        projectEdge(lines.lineArr[i], edges.edgeArr[i]);
    return statusCode;
}

Status projectModelTo2DPlane(ModelProj& proj, const Model3D& model)
{

    Status statusCode = modelCheck(model);
    if (statusCode != success)
        return statusCode;
    statusCode = projectPoints(proj.canvasPoints, model.points);
    if (statusCode == success)
    {
        statusCode = projectEdges(proj.lines, model.edges);
        if (statusCode != success)
            freeLines(proj.lines);
    }
    return statusCode;
}

/*
 * Transform section
 */

void transformPoint(Point& point, const Matrix& transfomMatrix)
{
    Vector coordsVector;
    initVector(coordsVector);
    convertPointToVector(coordsVector, point);
    applyMatrixToVector(coordsVector, transfomMatrix);
    convertVectorToPoint(point, coordsVector);
}

MoveVector makeMoveModelToCenterVector(const Point& pivot)
{
    MoveVector moveVector;
    moveVector.dx = -pivot.x;
    moveVector.dy = -pivot.y;
    moveVector.dz = -pivot.z;
    return moveVector;
}

MoveVector makeMoveModelToPivotVector(const Point& pivot)
{
    MoveVector moveVector;
    moveVector.dx = pivot.x;
    moveVector.dy = pivot.y;
    moveVector.dz = pivot.z;
    return moveVector;
}

Status transformPoints(PointArr& points, const Matrix& transformMatrix)
{
    Status statusCode = pointsCheck(points);
    if (statusCode == success)
        for (int i = 0; i < points.pointCount; i++)
            transformPoint(points.pointArr[i], transformMatrix);
    return statusCode;
}

//Move

Status moveModelPoints(Model3D& model, const MoveVector& moveVector)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    makeMoveMatrix(transformMatrix, moveVector);

    transformPoint(model.pivot, transformMatrix);
    return transformPoints(model.points, transformMatrix);
}

Status modelMove(Model3D& model, const MoveVector& moveVector)
{
    Status statusCode = modelCheck(model);
    if (statusCode == success)
        statusCode = moveModelPoints(model, moveVector);
    return statusCode;
}

//Scale

Status moveModelToCenter(Model3D& model)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    MoveVector moveVector = makeMoveModelToCenterVector(model.pivot);
    makeMoveMatrix(transformMatrix, moveVector);

    return transformPoints(model.points, transformMatrix);
}

Status moveModelToPivot(Model3D& model)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    MoveVector moveVector = makeMoveModelToPivotVector(model.pivot);
    makeMoveMatrix(transformMatrix, moveVector);

    return transformPoints(model.points, transformMatrix);
}

Status scaleModelPoints(PointArr& points, const ScaleRatio& scaleRatio)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    makeScaleMatrix(transformMatrix, scaleRatio);

    return transformPoints(points, transformMatrix);
}

Status modelScale(Model3D& model, const ScaleRatio& scaleRatio)
{
    Status statusCode = modelCheck(model);

    if (statusCode == success)
        statusCode = moveModelToCenter(model);

    if (statusCode == success)
        statusCode = scaleModelPoints(model.points, scaleRatio);

    if (statusCode == success)
        statusCode = moveModelToPivot(model);

    return statusCode;
}

//Rotate

Status rotatePointsOX(PointArr& points, float degX)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    makeOXRotationMatrix(transformMatrix, degX);
    return transformPoints(points, transformMatrix);
}

Status rotatePointsOY(PointArr& points, float degY)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    makeOYRotationMatrix(transformMatrix, degY);
    return transformPoints(points, transformMatrix);
}

Status rotatePointsOZ(PointArr& points, float degZ)
{
    Matrix transformMatrix;
    initMatrix(transformMatrix);

    makeOZRotationMatrix(transformMatrix, degZ);
    return transformPoints(points, transformMatrix);
}

Status rotateModelPoints(PointArr& points, const RotationAngle& rotationAngle)
{
    Status statusCode = rotatePointsOX(points, rotationAngle.degX);
    if (statusCode == success)
        statusCode = rotatePointsOY(points, rotationAngle.degY);
    if (statusCode == success)
        statusCode = rotatePointsOZ(points, rotationAngle.degZ);
    return statusCode;
}

Status modelRotate(Model3D& model, const RotationAngle& rotationAngle)
{
    Status statusCode = modelCheck(model);
    if (statusCode == success)
        statusCode = moveModelToCenter(model);

    if (statusCode == success)
        statusCode = rotateModelPoints(model.points, rotationAngle);

    if (statusCode == success)
        statusCode = moveModelToPivot(model);

    return statusCode;
}
