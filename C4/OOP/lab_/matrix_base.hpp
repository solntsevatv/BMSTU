#pragma once
#include <cstddef>

// Base interface matrix class
class MatrixBase {
public:
    // Constructor
    MatrixBase(size_t rows = 0, size_t columns = 0): _rows(rows), _cols(columns) {}

    // Virtual methods
    virtual size_t GetColumns() const { return _cols; };
    virtual size_t GetRows() const { return _rows; };
    virtual operator bool() const { return _cols && _rows; }
    
    // Virtual destructor
    virtual ~MatrixBase() = 0;

protected:
    // Protected data variables
    size_t _rows = 0, _cols = 0;
};

MatrixBase::~MatrixBase() {}
