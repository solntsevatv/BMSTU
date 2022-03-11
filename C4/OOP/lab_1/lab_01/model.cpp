#include "model.h"
#include "modelFileFuncs.h"
#include "modelDestroyData.h"
#include "modelTransformFuncs.h"

/*
 * Model init block
 */

Point pivotInit()
{
    Point pivot;
    pivot.x = 0;
    pivot.y = 0;
    pivot.z = 0;
    return pivot;
}

PointArr pointsInit()
{
    PointArr points;
    points.pointCount = 0;
    points.pointArr = NULL;
    return points;
}

EdgeArr edgesInit()
{
    EdgeArr edges;
    edges.edgeArr = NULL;
    edges.edgeCount = 0;
    return edges;
}

Model3D modelInit()
{
    Model3D model;
    model.edges = edgesInit();
    model.points = pointsInit();
    model.pivot = pivotInit();
    return model;
}

/*
 * Projection init block
 */

CanvasPointArr canvasPointsInit()
{
    CanvasPointArr canvasPoints;
    canvasPoints.canvasPointArr = NULL;
    canvasPoints.pointCount = 0;
    return canvasPoints;
}

LineArr linesInit()
{
    LineArr lines;
    lines.lineArr = NULL;
    lines.lineCount = 0;
    return lines;
}

ModelProj modelProjInit()
{
    ModelProj modelProjection;
    modelProjection.canvasPoints = canvasPointsInit();
    modelProjection.lines = linesInit();
    return modelProjection;
}

/*
 * Check model
 */

Status pointsCheck(const PointArr& points)
{
    if (points.pointCount == 0)
        return err_model_empty;
    if (points.pointArr == NULL)
        return err_model_empty;
    return success;
}

Status edgesCheck(const EdgeArr& edges)
{
    if (edges.edgeCount == 0)
        return err_model_empty;
    if (edges.edgeArr == NULL)
        return err_model_empty;
    return success;
}

Status modelCheck(const Model3D& model)
{
    Status statusCode = pointsCheck(model.points);
    if (statusCode == success)
        statusCode = edgesCheck(model.edges);
    return statusCode;
}

/*
 * Move model data
 */

// Move points

void movePointData(Point& pointDst, const Point& pointSrc)
{
    pointDst.x = pointSrc.x;
    pointDst.y = pointSrc.y;
    pointDst.z = pointSrc.z;
}

void movePointsData(PointArr& pointsDst, const PointArr& pointsSrc)
{
    pointsDst.pointCount = pointsSrc.pointCount;
    pointsDst.pointArr = pointsSrc.pointArr;
}

// Move edge data

void moveEdgesData(EdgeArr& edgesDst, const EdgeArr& edgesSrc)
{
    edgesDst.edgeCount = edgesSrc.edgeCount;
    edgesDst.edgeArr = edgesSrc.edgeArr;
}

void moveModelData(Model3D& modelDst, Model3D modelSrc)
{
    movePointData(modelDst.pivot, modelSrc.pivot);
    movePointsData(modelDst.points, modelSrc.points);
    moveEdgesData(modelDst.edges, modelSrc.edges);
}

/*
 * Copy projection
 */

// Move lines

void moveLines(LineArr& linesDst, const LineArr& linesSrc)
{
    linesDst.lineCount = linesSrc.lineCount;
    linesDst.lineArr = linesSrc.lineArr;
}

// Move canvas points

void moveCanvasPoints(CanvasPointArr& canvasPointsDst, const CanvasPointArr& canvasPointsSrc)
{
    canvasPointsDst.pointCount = canvasPointsSrc.pointCount;
    canvasPointsDst.canvasPointArr = canvasPointsSrc.canvasPointArr;
}

void moveProjData(ModelProj& projDst, const ModelProj& projSrc)
{
    moveCanvasPoints(projDst.canvasPoints, projSrc.canvasPoints);
    moveLines(projDst.lines, projSrc.lines);
}

/*
 * Model functions
 */

Status modelLoad(Model3D& model, const char* filename)
{
    FILE* file = fopen(filename, "r");

    if (!file)
        return err_load_file_incorrect;

    Model3D buffModel = modelInit();
    Status statusCode = getModelFromFile(buffModel, file);
    fclose(file);

    if (statusCode == success)
    {
        clearModel(model);
        moveModelData(model, buffModel);
    }

    return statusCode;
}

Status modelSave(Model3D& model, const char* filename)
{
    FILE* file = fopen(filename, "w");

    if (!file)
        return err_load_file_incorrect;
    Status statusCode = printModelInFile(model, file);
    fclose(file);
    return statusCode;
}

Status modelProject(ModelProj& currentProj, const Model3D& model)
{   
    Status statusCode = modelCheck(model);
    if (statusCode != success)
        return statusCode;
    ModelProj buffProj = modelProjInit();
    statusCode = projectModelTo2DPlane(buffProj, model);
    if (statusCode == success)
    {
        clearProjection(currentProj);
        moveProjData(currentProj, buffProj);
    }
    return statusCode;
}

Status modelOperator(ModelProj& modelCurrProject, Action& action)
{
    Status statusCode = success;
    static Model3D model = modelInit();
    switch(action.type)
    {
        case LOAD:
            statusCode = modelLoad(model, action.filename);
            break;
        case SAVE:
            statusCode = modelSave(model, action.filename);
            break;
        case MOVE:
            statusCode = modelMove(model, action.moveVector);
            break;
        case SCALE:
            statusCode = modelScale(model, action.scaleRatio);
            break;
        case ROTATE:
            statusCode = modelRotate(model, action.rotationAngle);
            break;
        case PROJECT:
            statusCode = modelProject(modelCurrProject, model);
            break;
        case CLEAR_MODEL:
            clearModel(model);
            break;
        default:
            statusCode = err_unknown_action_type;
            break;
     }
    return statusCode;
}
