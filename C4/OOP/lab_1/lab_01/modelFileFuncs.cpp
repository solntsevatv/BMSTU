#include "modelFileFuncs.h"

// DONE

/*
 * Load section
 */

Status copyCount(int& CountDst, int CountSrc)
{
    if (CountSrc < 0)
        return err_data_incorrect;
    CountDst = CountSrc;
    return success;
}

// Load points

Status getPointFromFile(Point &modelPoint, FILE *file)
{
    if (std::fscanf(file, "%f %f %f", &(modelPoint.x), &(modelPoint.y), &(modelPoint.z)) != 3)
        return err_load_file_data_incorrect;
    return success;
}

Status allocatePoints(PointArr& points, int pointCount)
{
    Status statusCode = copyCount(points.pointCount, pointCount);
    if (statusCode != success)
        return statusCode;
    points.pointArr = (Point*)malloc(sizeof(Point) * pointCount);
    if (points.pointArr == NULL)
        return err_memory_allocation_error;
    return success;
}

Status getPointCount(int& pointCount, FILE *file)
{
    if (std::fscanf(file, "%i\n", &pointCount) != 1)
        return err_load_file_data_incorrect;
    return success;
}

Status scanPointsFromFile(PointArr& points, FILE *file)
{
    int count;
    Status statusCode = getPointCount(count, file);
    if (statusCode == success)
        statusCode = allocatePoints(points, count);

    for (int i = 0; i < points.pointCount && statusCode == success; i++)
        statusCode = getPointFromFile(points.pointArr[i], file);
    if (statusCode != success)
        freePoints(points);
    return statusCode;
}

// Load edge

Status getEdgeFromFile(Edge &modelEdge, FILE* file)
{
    if (std::fscanf(file, "%i %i",&(modelEdge.startIndex), &(modelEdge.endIndex)) != 2)
        return err_load_file_data_incorrect;
    return success;
}

Status allocateEdges(EdgeArr& edges, int edgeCount)
{
    Status statusCode = copyCount(edges.edgeCount, edgeCount);
    if (statusCode != success)
        return statusCode;
    edges.edgeArr = (Edge*)malloc(sizeof(Edge) * edgeCount);
    if (edges.edgeArr == NULL)
        return err_memory_allocation_error;
    return success;
}

Status getEdgeCount(int& edgeCount, FILE *file)
{
    if (std::fscanf(file, "%i\n", &edgeCount) != 1)
        return err_load_file_data_incorrect;
    return success;
}

Status scanEdgesFromFile(EdgeArr& edges, FILE *file)
{
    Status statusCode = getEdgeCount(edges.edgeCount, file);
    if (statusCode == success)
        statusCode = allocateEdges(edges, edges.edgeCount);
    for (int i = 0; i < edges.edgeCount && statusCode == success; i++)
        statusCode = getEdgeFromFile(edges.edgeArr[i], file);
    if (statusCode != success)
        freeEdges(edges);
    return statusCode;
}

// Load model

Status getModelFromFile(Model3D &model, FILE* file)
{
    Status statusCode = success;

    statusCode = getPointFromFile(model.pivot, file);
    if (statusCode == success)
        statusCode = scanPointsFromFile(model.points, file);
    if (statusCode == success)
    {
        statusCode = scanEdgesFromFile(model.edges, file);
        if (statusCode != success)
            freePoints(model.points);
    }
    return statusCode;
}

/*
 * Save section
 */

// Print points

void printProintInFile(Point modelPoint, FILE *file)
{
    std::fprintf(file, "%f %f %f\n", modelPoint.x, modelPoint.y, modelPoint.z);
}

void printPointArrInFile(const PointArr& points, FILE *file)
{
    for (int i = 0; i < points.pointCount; i++)
        printProintInFile(points.pointArr[i], file);
}

void printPointCountInFile(int pointCount, FILE *file)
{
    std::fprintf(file, "%i\n", pointCount);
}

void printPointsInFile(const PointArr& points, FILE *file)
{
    printPointCountInFile(points.pointCount, file);
    printPointArrInFile(points, file);
}

// Print edges

void printEdgeInFile(Edge modelEdge, FILE *file)
{
    std::fprintf(file, "%i %i\n", modelEdge.startIndex, modelEdge.endIndex);
}

void printEdgeArrInFile(const EdgeArr& edges, FILE *file)
{
    for (int i = 0; i < edges.edgeCount; i++)
        printEdgeInFile(edges.edgeArr[i], file);
}

void printEdgeCountInFile(int edgeCount, FILE *file)
{
    std::fprintf(file, "%i\n", edgeCount);
}

void printEdgesInFile(const EdgeArr& edges, FILE *file)
{
    printEdgeCountInFile(edges.edgeCount, file);
    printEdgeArrInFile(edges, file);
}

// Print model

Status printModelInFile(const Model3D& model, FILE* file)
{
    Status statusCode = modelCheck(model);
    if (statusCode != success)
        return statusCode;
    printProintInFile(model.pivot, file);
    printPointsInFile(model.points, file);
    printEdgesInFile(model.edges, file);

    return statusCode;
}
