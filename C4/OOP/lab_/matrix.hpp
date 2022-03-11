#pragma once
#include <iostream>
#include <memory>
#include <iterator>

#include "exception.hpp"
#include "matrix_base.hpp"
#include "const_iterator.hpp"
#include "iterator.hpp"

template <typename Type>
using SharedPtr = std::shared_ptr<Type>;
using string = std::string;

// Main matrix class
template <typename Type>
class Matrix: public MatrixBase {
public:
    // Iterators
    friend Iterator<Type>;
    friend ConstIterator<Type>;
        
    // Subclass for matrix row operations
    class MatrixRow;

public:
    // Empty matrix
    explicit Matrix(size_t rows = 0, size_t columns = 0);
    // Filled matrix
    Matrix(size_t rows, size_t columns, const Type &filler);
    // C-matrix constructor
    Matrix(size_t rows, size_t columns, Type **matrix);
    // Matrix from const matrix constructor
    explicit Matrix(const Matrix &matrix);
    // Matrix from matrix constructor
    Matrix(Matrix &&matrix);
    // Initializer list
    Matrix(std::initializer_list<std::initializer_list<Type> > init_list);
    
    // Destructor generation
    virtual ~Matrix() = default;

    // Matrix const pointer operator
    Matrix<Type> &operator=(const Matrix &matrix);
    // Matrix pointer operator
    Matrix<Type> &operator=(Matrix &&matrix);
    // Initializer list operator
    Matrix<Type>& operator=(std::initializer_list<std::initializer_list<Type> > init_list);
    
    // Check if square, true if yes, false if no
    bool isSquare() const;
    // Count determinant
    Type determinant() const;
    // Transpose matrix
    void transpose();
    // Inverse matrix
    void inverse();

    // Constant iterators
    ConstIterator<Type> begin() const;
    ConstIterator<Type> end() const;

    // Iterators
    Iterator<Type> begin();
    Iterator<Type> end();

    // C-iterators
    ConstIterator<Type> cbegin() const;
    ConstIterator<Type> cend() const;

    // Fill matrix
    // Fill with value from start to end
    void fill(Iterator<Type> start, const Iterator<Type> &end, const Type &value);
    // Fill form constartn source from start to end
    void fill(Iterator<Type> start, ConstIterator<Type> source_start, const ConstIterator<Type> &source_end);
    // Fill from source from start to end
    void fill(Iterator<Type> start, Iterator<Type> source_start, const Iterator<Type> &source_end);

    // Resize matrix
    void resize(size_t new_rows, size_t new_cols, const Type &filler = {});
    // Resize by rows
    void resizeRows(size_t new_size, const Type &filler = {});
    // Resize by cols
    void resizeCols(size_t new_size, const Type &filler = {});

    // Insert row
    void insertRow(size_t pos, const Type &filler = {});
    // Instert column
    void insertCol(size_t pos, const Type &filler = {});

    // Delete row
    void deleteRow(size_t pos);
    // Delete column
    void deleteCol(size_t pos);

    // Matrix equality overload method
    bool checkEqual(const Matrix& matrix) const;
    // Matrix equality overload operator
    bool operator==(const Matrix& matrix) const;
    // Matrix inequality overload method
    bool checkUnequal(const Matrix& matrix) const;
    // Matrix inequality overloda operator
    bool operator!=(const Matrix& matrix) const;

    // Matrix get row by index operator
    MatrixRow operator[](size_t row);
    // Get matrix element at position
    Type& at(size_t row, size_t col);
    // Get pointer for elemet at row col position
    Type& operator()(size_t row, size_t col);

    // Matrix get const row by index operator
    const MatrixRow operator[](size_t row) const;
    // Get constant matrix element at row col position
    const Type& at(size_t row, size_t col) const;
    // Get constant pointer for element at row col position
    const Type& operator()(size_t row, size_t col) const;

    // Add methods
    // Adds matrix to matrix element by element
    Matrix<Type> addMatrix(const Matrix& matrix) const noexcept;
    Matrix<Type> operator+(const Matrix& matrix) const noexcept;
    // Add elem to every element of matrix
    Matrix<Type> addElem(const Type& elem) const noexcept;
    Matrix<Type> operator+(const Type& elem) const noexcept;

    // Substraction methods
    // Substract  matrix
    Matrix<Type> subMatrix(const Matrix& matrix) const noexcept;
    Matrix<Type> operator-(const Matrix& matrix) const noexcept;
    // Substract element
    Matrix<Type> subElem(const Type& elem) const noexcept;
    Matrix<Type> operator-(const Type& elem) const noexcept;

    // Multiplication methods
    // Multiply by matrix
    Matrix<Type> mulMatrix(const Matrix& matrix) const;
    Matrix<Type> operator*(const Matrix& matrix) const;
    // Multiply by element
    Matrix<Type> mulElem(const Type& elem) const noexcept;
    Matrix<Type> operator*(const Type& elem) const noexcept;

    // Division methods
    // Divide by matrix
    Matrix<Type> divMatrix(const Matrix& matrix) const;
    Matrix<Type> operator/(const Matrix& matrix) const;
    // Divide by element
    Matrix<Type> divElem(const Type & elem) const;
    Matrix<Type> operator/(const Type& elem) const;

    // Negative matrix 
    Matrix<Type> neg();
    // Negative matrix operator
    Matrix<Type> operator-();

    // Add matrix and assign
    Matrix<Type>& addAssigMatrix(const Matrix& matrix);
    // Add matrix and assign operator
    Matrix<Type>& operator+=(const Matrix& matrix);
    // Add element and assign
    Matrix<Type>& addAssigElem(const Type& elem) noexcept;
    // Add element and assign operator
    Matrix<Type>& operator+=(const Type& elem) noexcept;

    // Substract matrix and assign 
    Matrix<Type>& subAssigMatrix(const Matrix& matrix);
    // Substract matrix and assign operator
    Matrix<Type>& operator-=(const Matrix& matrix);
    // Substract element and assign
    Matrix<Type>& subAssigElem(const Type& elem) noexcept;
    // Substract element and assign operator
    Matrix<Type>& operator-=(const Type& elem) noexcept;

    // Multiply by matrix and assign
    Matrix<Type>& mulAssigMatrix(const Matrix& matrix);
    // Multiply by matrix and assign operator
    Matrix<Type>& operator*=(const Matrix& matrix);
    // Multiply by element and assign 
    Matrix<Type>& mulAssigElem(const Type& elem) noexcept;
    // Multiply by element and assign operator
    Matrix<Type>& operator*=(const Type& elem) noexcept;
    
    // Divide by matrix and assign
    Matrix<Type>& divAssigMatrix(const Matrix& matrix);
    // Divide by matrix and assign operator
    Matrix<Type>& operator/=(const Matrix& matrix);
    // Divide by element and assign
    Matrix<Type>& divAssigElem(const Type& elem);
    // Divide by element and assign operator
    Matrix<Type>& operator/=(const Type& elem);

private:
    // Shared pointers to matrix row data
    SharedPtr<MatrixRow[]> _data { nullptr };
    // Method for memory allocation
    SharedPtr<MatrixRow[]> _allocMemory(size_t rows, size_t cols);
    // Move row from position to position inside matrix
    void _moveRow(size_t from, size_t to);
    // Move column from position to position inside matrix
    void _moveCol(size_t from, size_t to);
    // Check if index of position is legit
    void _checkIndex(size_t pos, size_t limit) const;
    // Check if size of matrix is equal
    void _checkSizes(const Matrix &matrix) const;
    // Check if matrix is compatable for multiplication
    void _checkMultSizes(const Matrix &matrix) const;

public:
    // Subclass for matrix row operations
    class MatrixRow {
        // Friend iterator class
        friend Iterator<Type>;
        // Friend constant iterator class
        friend ConstIterator<Type>;

    private:
        // Matrix row data
        SharedPtr<Type[]> _data = nullptr;
        // Size of row
        size_t _size = 0;

    public:
        // Constructors
        MatrixRow(Type *data, const size_t size): _data(data), _size(size) {}
        MatrixRow(): _data(nullptr), _size(0) {}
        
        // Get element by index operator
        Type &operator[](size_t index);
        // Get constant element by index operator
        const Type &operator[](size_t index) const;

        // Reset row with new values
        void reset(Type *data, const size_t size);
        // Reset row
        void reset();
    };
};

#include "matrix_constructs_and_eqopers.hpp"
#include "matrix_form_operations.hpp"
#include "matrix_iterators.hpp"
#include "matrix_math.hpp"
#include "matrix_oper_methods.hpp"
#include "matrix_operators.hpp"
#include "matrix_private.hpp"
#include "matrix_rest_methods.hpp"
#include "matrix_row.hpp"
