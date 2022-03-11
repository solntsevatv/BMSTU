#include "matrix.h"

Matrix::Matrix()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] = 0;
        }
    }
}

Matrix::Matrix(Matrix &matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] = matrix.data_[i][j];
        }
    }
}

Matrix::Matrix(float data[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] = data[i][j];
        }
    }
}

void Matrix::operator=(const Matrix &matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] = matrix.data_[i][j];
        }
    }
}

Matrix Matrix::dot(Matrix matrix)
{
    Matrix result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.data_[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                result.data_[i][j] += data_[i][k] * matrix.data_[k][j];
            }
        }
    }

    return result;
}

void Matrix::identity()
{
    for (int i = 0; i < 4; i++)
    {
        data_[i][i] = 1;
    }
}

void Matrix::sum(Matrix &matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] += matrix.data_[i][j];
        }
    }
}

void Matrix::sum(float num)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] += num;
        }
    }
}

void Matrix::sub(Matrix &matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] -= matrix.data_[i][j];
        }
    }
}

void Matrix::sub(float num)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] -= num;
        }
    }
}

void Matrix::mult(Matrix &matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] *= matrix.data_[i][j];
        }
    }
}

void Matrix::mult(float num)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] *= num;
        }
    }
}

void Matrix::div(Matrix &matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix.data_[i][j] != 0)
                data_[i][j] /= matrix.data_[i][j];
        }
    }
}

void Matrix::div(float num)
{
    if (num != 0)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                data_[i][j] /= num;
            }
        }
    }
}

void Matrix::neg()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data_[i][j] *= -1;
        }
    }
}

Matrix Matrix::inverse_4x4()
{
    Matrix matrix;
    matrix.data_[0][0] = data_[0][0]; matrix.data_[0][1] = data_[1][0]; matrix.data_[0][2] = data_[2][0]; matrix.data_[0][3] = 0.0f;
    matrix.data_[1][0] = data_[0][1]; matrix.data_[1][1] = data_[1][1]; matrix.data_[1][2] = data_[2][1]; matrix.data_[1][3] = 0.0f;
    matrix.data_[2][0] = data_[0][2]; matrix.data_[2][1] = data_[1][2]; matrix.data_[2][2] = data_[2][2]; matrix.data_[2][3] = 0.0f;
    matrix.data_[3][0] = -(data_[3][0] * matrix.data_[0][0] + data_[3][1] * matrix.data_[1][0] + data_[3][2] * matrix.data_[2][0]);
    matrix.data_[3][1] = -(data_[3][0] * matrix.data_[0][1] + data_[3][1] * matrix.data_[1][1] + data_[3][2] * matrix.data_[2][1]);
    matrix.data_[3][2] = -(data_[3][0] * matrix.data_[0][2] + data_[3][1] * matrix.data_[1][2] + data_[3][2] * matrix.data_[2][2]);
    matrix.data_[3][3] = 1.0f;
    return matrix;
}

float Matrix::determinant_2x2()
{
    float submatrix[2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            submatrix[i][j] = data_[i][j];
        }
    }
    return determinant_2x2(submatrix);
}

float Matrix::determinant_2x2(float a, float b, float c, float d)
{
    return a * d - b * c;
}

float Matrix::determinant_2x2(float matrix[2][2])
{
    float a = matrix[0][0];
    float b = matrix[0][1];
    float c = matrix[1][0];
    float d = matrix[1][1];
    return a * d - b * c;
}

float Matrix::determinant_3x3()
{
    float submatrix[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            submatrix[i][j] = data_[i][j];
        }
    }
    return determinant_3x3(submatrix);
}

float Matrix::determinant_3x3(float matrix[3][3])
{
    float temp_1[2][2] = {{matrix[1][1], matrix[1][2]}, {matrix[2][1], matrix[2][2]}};
    float temp_2[2][2] = {{matrix[1][0], matrix[1][2]}, {matrix[2][0], matrix[2][2]}};
    float temp_3[2][2] = {{matrix[1][0], matrix[1][1]}, {matrix[2][0], matrix[2][1]}};
    return matrix[0][0] * determinant_2x2(temp_1) - matrix[0][1] * determinant_2x2(temp_2) + matrix[0][2] * determinant_2x2(temp_3);
}

float Matrix::determinant_4x4()
{
    return determinant_4x4(data_);
}

float Matrix::determinant_4x4(float matrix[4][4])
{
    float temp_1[3][3] = {
        {matrix[1][1], matrix[1][2], matrix[1][3]},
        {matrix[2][1], matrix[2][2], matrix[2][3]},
        {matrix[3][1], matrix[3][2], matrix[3][3]}
    };

    float temp_2[3][3] = {
        {matrix[1][0], matrix[1][2], matrix[1][3]},
        {matrix[2][0], matrix[2][2], matrix[2][3]},
        {matrix[3][0], matrix[3][2], matrix[3][3]}
    };

    float temp_3[3][3] = {
        {matrix[1][0], matrix[1][1], matrix[1][3]},
        {matrix[2][0], matrix[2][1], matrix[2][3]},
        {matrix[3][0], matrix[3][1], matrix[3][3]}
    };

    float temp_4[3][3] = {
        {matrix[1][0], matrix[1][1], matrix[1][2]},
        {matrix[2][0], matrix[2][1], matrix[2][2]},
        {matrix[3][0], matrix[3][1], matrix[3][2]}
    };

    float result = 0;
    result += determinant_3x3(temp_1) * matrix[0][0];
    result += determinant_3x3(temp_2) * matrix[0][1];
    result += determinant_3x3(temp_3) * matrix[0][2];
    result += determinant_3x3(temp_4) * matrix[0][3];
    return result;
}
