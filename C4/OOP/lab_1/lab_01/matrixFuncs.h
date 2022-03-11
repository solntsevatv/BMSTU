#ifndef MATRIXFUNCS_H
#define MATRIXFUNCS_H

#include <math.h>
#include "model.h"
#include "head.h"

void initMatrix(Matrix& matrix);
void initVector(Vector& vector);
void makeMoveMatrix(Matrix& matrix, const MoveVector& moveVector);
void makeScaleMatrix(Matrix& matrix, const ScaleRatio& scaleRatio);
void makeOXRotationMatrix(Matrix& matrix, float degX);
void makeOYRotationMatrix(Matrix& matrix, float degY);
void makeOZRotationMatrix(Matrix& matrix, float degZ);
void copyVector(Vector& vectorDst, Vector& vectorSrc);
void applyMatrixToVector(Vector& vector, const Matrix& matrix);
void convertPointToVector(Vector& vector, const Point& point);
void convertVectorToPoint(Point& point, const Vector& vector);

#endif // MATRIXFUNCS_H
