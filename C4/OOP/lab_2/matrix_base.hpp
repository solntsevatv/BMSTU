#pragma once

class MatrixBase {
public:
	// Constructor
	MatrixBase(size_t rows = 0, size_t cols = 0): _rows(rows), _cols(cols) {};
	// Destructor
	virtual ~MatrixBase() = 0;

	// Base virtual methods
	virtual size_t Rows() const noexcept { return _rows; };
	virtual size_t Cols() const noexcept { return _cols; };

protected:
	// Rows & cols
	size_t _rows = 0;
	size_t _cols = 0;
};
