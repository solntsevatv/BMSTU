#ifndef MODELFILEFUNCS_H
#define MODELFILEFUNCS_H

#include "head.h"
#include "model.h"
#include "modelDestroyData.h"

Status getModelFromFile(Model3D &model, FILE* file);
Status printModelInFile(const Model3D& model, FILE* file);
Status allocatePoints(PointArr& points, int pointCount);
Status allocateEdges(EdgeArr& edges, int edgeCount);
Status copyCount(int& CountDst, int CountSrc);

#endif // MODELFILEFUNCS_H
