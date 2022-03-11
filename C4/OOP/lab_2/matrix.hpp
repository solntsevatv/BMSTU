#pragma once
#include <iostream>
#include <memory>

// Unique ptr for matrix data storage
template <typename T>
using ptrShrd = std::shared_ptr<T>;

#include "matrix_base.hpp"
#include "matrix_iterator.hpp"
#include "matrix_exception.hpp"

// Matrix class
template <typename T>
class Matrix : public MatrixBase
{
public:
    // Iterator
    friend MatrixIterator<T>;
    // Const iterator
    friend MatrixConstIterator<T>;

    // Subclass for matrix row
    class MatrixRow;

public:
    // Constructors
    // Standart constructor
    explicit Matrix(size_t rows = 0, size_t columns = 0);
    // Copy constructor
    explicit Matrix(const Matrix& matrix);
    // Constructor with filler
    Matrix(size_t rows, size_t columns, const T& filler);
    // C-matrix constructor
    Matrix(size_t rows, size_t columns, T** matrix);
    // C-matrix copy constructor
    Matrix(Matrix&& matrix) noexcept; 

    // Const assign operator
    Matrix<T>& operator=(const Matrix& matrix);
    // Assign operator
    Matrix<T>& operator=(Matrix&& matrix);
    // Initializer list assign operator
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T> > init_list);

    // Initializer list matrix constructor
    Matrix(std::initializer_list<std::initializer_list<T> > init_list); 

    // Create identity matrix
    explicit Matrix<T> IdentityMatrix(size_t size);

    // Default estructor generation
    virtual ~Matrix() = default;

    // Iterators
    MatrixIterator<T> begin() noexcept;
    MatrixIterator<T> end() noexcept;
    // Constant iterators
    MatrixConstIterator<T> begin() const noexcept;
    MatrixConstIterator<T> end() const noexcept;
    // C-iterators
    MatrixConstIterator<T> cbegin() const noexcept;
    MatrixConstIterator<T> cend() const noexcept;

    // Matrix equality overload method
    bool equal(const Matrix& matrix) const noexcept; 
    // Matrix equality overload operator
    bool operator==(const Matrix& matrix) const noexcept;
    // Matrix inequality overload method
    bool unequal(const Matrix& matrix) const noexcept;
    // Matrix inequality overloda operator
    bool operator!=(const Matrix& matrix) const noexcept;
    
    // Matrix get row by index operator
    MatrixRow operator[](size_t row);
    // Get pointer for elemet at row col position
    T& operator()(size_t row, size_t col);
    // Get matrix element at position
    T& at(size_t row, size_t col);

    // Matrix get const row by index operator
    const MatrixRow operator[](size_t row) const; 
    // Get constant pointer for element at row col position
    const T& operator()(size_t row, size_t col) const;
    // Get constant matrix element at row col position
    const T& at(size_t row, size_t col) const;

    // Check if square
    bool square() const noexcept;
    // Count determinant
    T determinant() const noexcept; 
    // Transpose matrix
    void transpose();
    // Inverse matrix
    void inverse();

    // Adds matrix to matrix element by element
    Matrix<T> add(const Matrix& matrix) const;
    Matrix<T> operator+(const Matrix& matrix) const;
    // Add elem to every element of matrix
    Matrix<T> addElem(const T& elem) const;
    Matrix<T> operator+(const T& elem) const;

    // Substracts matrix element by element
    Matrix<T> sub(const Matrix& matrix) const;
    Matrix<T> operator-(const Matrix& matrix) const;
    // Substract element from matrix element by element
    Matrix<T> subElem(const T& elem) const;
    Matrix<T> operator-(const T& elem) const;

    // Dot matrix
    Matrix<T> dot(const Matrix& matrix) const;
    Matrix<T> operator*(const Matrix& matrix) const;
    // Multiply matrix element by element
    Matrix<T> mulElem(const T& elem) const;
    Matrix<T> operator*(const T& elem) const;
    // Multiply matrix by matrix element by element
    Matrix<T> mulElem(const Matrix& matrix) const;

    // Divide matrix by matrix rules
    Matrix<T> div(const Matrix& matrix) const;
    Matrix<T> operator/(const Matrix& matrix) const;
    // Divide matrix element by element
    Matrix<T> divElem(const T& elem) const;
    Matrix<T> operator/(const T& elem) const;
    // Divide matrix by matrix element by element
    Matrix<T> divElem(const Matrix& matrix) const;

    // Negative matrix 
    Matrix<T> negative() noexcept;
    // Negative matrix operator
    Matrix<T> operator-() noexcept;

    // Add matrix and assign
    Matrix<T>& addAssigMatrix(const Matrix& matrix);
    // Add matrix and assign operator
    Matrix<T>& operator+=(const Matrix& matrix);
    // Add element and assign
    Matrix<T>& addAssigElem(const T& elem);
    // Add element and assign operator
    Matrix<T>& operator+=(const T& elem);

    // Substract matrix and assign 
    Matrix<T>& subAssigMatrix(const Matrix& matrix);
    // Substract matrix and assign operator
    Matrix<T>& operator-=(const Matrix& matrix);
    // Substract element and assign
    Matrix<T>& subAssigElem(const T& elem);
    // Substract element and assign operator
    Matrix<T>& operator-=(const T& elem);

    // Multiply by matrix and assign
    Matrix<T>& mulAssigMatrix(const Matrix& matrix);
    // Multiply by matrix and assign operator
    Matrix<T>& operator*=(const Matrix& matrix);
    // Multiply by element and assign 
    Matrix<T>& mulAssigElem(const T& elem);
    // Multiply by element and assign operator
    Matrix<T>& operator*=(const T& elem);
    // Multiply element by element and assign
    Matrix<T>& mulAssigElem(const Matrix& matrix);

    // Divide by matrix and assign
    Matrix<T>& divAssigMatrix(const Matrix& matrix);
    // Divide by matrix and assign operator
    Matrix<T>& operator/=(const Matrix& matrix);
    // Divide by element and assign (math)
    Matrix<T>& divAssigElem(const T& elem);
    // Divide by element and assign operator
    Matrix<T>& operator/=(const T& elem);
    // Divide by element and assign (simple)
    Matrix<T>& divAssigElem(const Matrix& matrix);

    // Fill with value from start to end
    void fill(MatrixIterator<T> start, const MatrixIterator<T>& end, const T& value);
    // Fill form constartn source from start to end
    void fill(MatrixIterator<T> start, MatrixConstIterator<T> src_start, const MatrixConstIterator<T>& src_end);
    // Fill from source from start to end
    void fill(MatrixIterator<T> start, MatrixIterator<T> src_start, const MatrixIterator<T>& src_end);

    // Resize matrix
    void resize(size_t rows, size_t cols, const T& filler = {});
    // Resize by rows
    void resizeRows(size_t new_size, const T& filler = {});
    // Resize by cols
    void resizeCols(size_t new_size, const T& filler = {});

    // Insert row
    void insertRow(size_t pos, const T& filler = {});
    // Instert column
    void insertCol(size_t pos, const T& filler = {});

    // Delete row
    void removeRow(size_t index);
    // Delete column
    void removeCol(size_t index);

private:
    // Shared pointer for matrix rows
    ptrShrd<MatrixRow[]> _data{ nullptr };

    // Relocate row from src to dst inside matrix
    void _relocateRow(size_t src, size_t dst);
    // Relocate column from src to dst inside matrix
    void _relocateCol(size_t src, size_t dst);

    void _validateSizeEqual(const Matrix<T>& matrix) const;
    void _validateSizeMatrMult(const Matrix<T>& matrix) const;

    // Memory allocator
    ptrShrd<Matrix<T>::MatrixRow[]> _allocData(size_t rows, size_t cols);

public:
    // Subclass for matrix row
    class MatrixRow {
        // Friend iterator class
        friend MatrixIterator<T>;
        // Friend constant iterator class
        friend MatrixConstIterator<T>;

    private:
        // Matrix row data
        ptrShrd<T[]> _data = nullptr;
        // Size of row
        size_t _size = 0;

    public:
        // Constructors
        MatrixRow(T* data, const size_t size) : _data(data), _size(size) {}
        MatrixRow() : _data(nullptr), _size(0) {}

        // Get element by index method
        T& atRow(size_t index);
        // Get element by index operator
        T& operator[](size_t index);
        // Get const raw element by index
        const T& operator[](size_t index) const;

        // Reset row with new values
        void reset(T* data, const size_t size);
        // Reset row completly
        void reset();
    };
};