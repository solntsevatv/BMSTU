#pragma once
#include <memory>
#include "matrix_exception.hpp"

// Weak ptr for data access 
template <typename T>
using ptrWeak = std::weak_ptr<T>;

// for data operations
template <typename T>
using ptrShrd = std::shared_ptr<T>;

// Matrix class
template <typename T>
class Matrix;

// Iterator class derived from std::iterator
template <typename T>
class MatrixConstIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
	// Iterator constructor
	MatrixConstIterator(const Matrix<T>& matrix, const size_t index = 0) :
		_index(index), _rows(matrix._rows), _cols(matrix._cols), _data(matrix._data) {}
	// Copy constructor
	MatrixConstIterator(const MatrixConstIterator& refIterator) = default;

	// Boolean section
	bool equal(MatrixConstIterator const& other) const noexcept;
	bool operator==(MatrixConstIterator const& other) const noexcept;

	bool unequal(MatrixConstIterator const& other) const noexcept;
	bool operator!=(MatrixConstIterator const& other) const noexcept;

	bool lesser(MatrixConstIterator const& other) const noexcept;
	bool operator<(MatrixConstIterator const& other) const noexcept;

	bool greater(MatrixConstIterator const& other) const noexcept;
	bool operator>(MatrixConstIterator const& other) const noexcept;

	// Index checkups
	bool valid() const noexcept;
	bool end() const noexcept;
	bool start() const noexcept;

	// Bool operator
	operator bool() const noexcept;

	// Pointer operations
	const T& operator*() const;
	const T& value() const;

	// Overloading reference operator
	const T* operator->() const;

	// Increment operator and method
	MatrixConstIterator<T>& operator++() const noexcept;
	MatrixConstIterator<T>& next() const noexcept;
	MatrixConstIterator<T> operator++(int) const noexcept;

	// Decrement operator and method
	MatrixConstIterator<T>& operator--() const noexcept;
	MatrixConstIterator<T>& previous() const noexcept;
	MatrixConstIterator<T> operator--(int) const noexcept;

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