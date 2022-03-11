#include "matrixFuncs.h"

//DONE

/*
 *  Matrix operations
 */

void initMatrix(Matrix& matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                matrix.data[i][j] = 1;
            else
                matrix.data[i][j] = 0;
        }
    }
}

void initVector(Vector& vector)
{
    for (int i = 0; i < 4; i++)
        vector.data[i] = 0;
}

void makeMoveMatrix(Matrix& matrix, const MoveVector& moveVector)
{
    initMatrix(matrix);
    matrix.data[0][3] = moveVector.dx;
    matrix.data[1][3] = moveVector.dy;
    matrix.data[2][3] = moveVector.dz;
}

void makeScaleMatrix(Matrix& matrix, const ScaleRatio& scaleRatio)
{
    initMatrix(matrix);
    matrix.data[0][0] = scaleRatio.ratioX;
    matrix.data[1][1] = scaleRatio.ratioY;
    matrix.data[2][2] = scaleRatio.ratioZ;
}

void makeOXRotationMatrix(Matrix& matrix, float degX)
{
    initMatrix(matrix);
    matrix.data[1][1] = cos(degX);
    matrix.data[1][2] = -sin(degX);
    matrix.data[2][1] = sin(degX);
    matrix.data[2][2] = cos(degX);
}

void makeOYRotationMatrix(Matrix& matrix, float degY)
{
    initMatrix(matrix);
    matrix.data[0][0] = cos(degY);
    matrix.data[0][2] = sin(degY);
    matrix.data[2][0] = -sin(degY);
    matrix.data[2][2] = cos(degY);
}

void makeOZRotationMatrix(Matrix& matrix, float degZ)
{
    initMatrix(matrix);
    matrix.data[2][2] = cos(degZ);
    matrix.data[2][3] = -sin(degZ);
    matrix.data[3][2] = sin(degZ);
    matrix.data[3][3] = cos(degZ);
}

/*
 *  Vector operations
 */

void copyVector(Vector& vectorDst, Vector& vectorSrc)
{
    for (int i = 0; i < 4; i++)
        vectorDst.data[i] = vectorSrc.data[i];
}

void applyMatrixToVector(Vector& vector, const Matrix& matrix)
{
    Vector newVector;
    initVector(newVector);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            newVector.data[i] += vector.data[j] * matrix.data[i][j];

    copyVector(vector, newVector);
}

void convertPointToVector(Vector& vector, const Point& point)
{
    vector.data[0] = point.x;
    vector.data[1] = point.y;
    vector.data[2] = point.z;
    vector.data[3] = 1;
}

void convertVectorToPoint(Point& point, const Vector& vector)
{
    point.x = vector.data[0];
    point.y = vector.data[1];
    point.z = vector.data[2];
}




