#ifndef MATRIX_H
#define MATRIX_H

// VERIFIED
class Matrix
{
public:
    Matrix(); //v
    Matrix(Matrix &matrix); //v
    Matrix(float data[4][4]); //v

    void operator= (const Matrix &matrix);

    Matrix dot(Matrix matrix);
    void identity();

    void sum(Matrix &matrix);
    void sum(float num);

    void sub(Matrix &matrix);
    void sub(float num);

    void mult(Matrix &matrix);
    void mult(float num);

    void div(Matrix &matrix);
    void div(float num);

    void neg();

    Matrix inverse_4x4();

    // Upper left square
    float determinant_2x2(); //v
    float determinant_2x2(float matrix[2][2]); //v
    float determinant_2x2(float a, float b, float c, float d); //v

    float determinant_3x3(); //v
    float determinant_3x3(float matrix[3][3]); //v

    float determinant_4x4(); //v
    float determinant_4x4(float matrix[4][4]); //v

    float data_[4][4]; //v
};

#endif // MATRIX_H
