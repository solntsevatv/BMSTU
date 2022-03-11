#pragma once
#include "matrix_const_iterator.hpp"

// Weak ptr for data access 
template <typename T>
using ptrWeak = std::weak_ptr<T>;

// Matrix class
template <typename T>
class Matrix;

// Iterator class derived from std::iterator
template <typename T>
class MatrixIterator : public MatrixConstIterator
{
public:
	// Iterator constructor
	MatrixIterator(const Matrix<T> &matrix, const size_t index = 0) :
		_index(index), _rows(matrix._rows), _cols(matrix._cols), _data(matrix._data) {}
	// Copy constructor
	MatrixIterator(const MatrixIterator& refIterator) = default;

	// Pointer operations
	T& operator*();
	T& value();

	// Overloading reference operator
	T* operator->();

	// Increment operator and method
	MatrixIterator<T>& operator++() noexcept;
	MatrixIterator<T>& next() noexcept;
	MatrixIterator<T> operator++(int) noexcept;

	// Decrement operator and method
	MatrixIterator<T>& operator--() noexcept;
	MatrixIterator<T>& previous() noexcept;
	MatrixIterator<T> operator--(int) noexcept;

	// Assign operator
	MatrixIterator<T>& assign(const MatrixIterator<T>& refIterator)  noexcept;
	MatrixIterator<T>& operator=(const MatrixIterator<T>& retIterator) noexcept;

private:
	// Check interator validity
	void _iterValid();
	// Index
	size_t _index = 0;
	// Matrix rows
	size_t _rows = 0;
	// Matrix columns
	size_t _cols = 0;
	// Weak ptr for matrix data access
	ptrWeak<typename Matrix<T>::MatrixRow[]> _data;
};