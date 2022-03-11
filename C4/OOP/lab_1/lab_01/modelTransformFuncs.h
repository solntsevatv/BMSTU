#ifndef MODELTRANSFORMFUNCS_H
#define MODELTRANSFORMFUNCS_H

#include "head.h"
#include "model.h"
#include "matrixFuncs.h"
#include "modelDestroyData.h"
#include "modelFileFuncs.h"

Status projectModelTo2DPlane(ModelProj& proj, const Model3D& model);

Status modelMove(Model3D& model, const MoveVector& moveVector);
Status modelScale(Model3D& model, const ScaleRatio& scaleRatio);
Status modelRotate(Model3D& model, const RotationAngle& rotationAngle);

#endif // MODELTRANSFORMFUNCS_H
