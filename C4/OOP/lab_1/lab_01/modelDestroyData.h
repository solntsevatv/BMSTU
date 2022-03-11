#ifndef MODELDESTROYDATA_H
#define MODELDESTROYDATA_H

#include "head.h"
#include "model.h"

void clearModel(Model3D& model);
void clearProjection(ModelProj& projection);

void freeEdges(EdgeArr& edges);
void freePoints(PointArr& points);

void freeCanvasPoints(CanvasPointArr& canvasPoints);
void freeLines(LineArr& lines);


#endif // MODELDESTROYDATA_H
