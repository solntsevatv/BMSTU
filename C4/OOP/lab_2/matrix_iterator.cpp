#include "matrix_iterator.hpp"

template <typename T>
void MatrixIterator<T>::_iterValid()
{
	if (!valid())
	{
		time_t cur_time = time(NULL);
		auto curtime = localtime(&cur_time);
		throw IteratorMemoryError(asctime(local_time), __FILE__, __LINE__, "Matrix data expired!");
	}

	if (!(_index < _rows * _cols))
	{
		time_t cur_time = time(NULL);
		auto local_time = localtime(&cur_time);
		throw IteratorIndexError(asctime(local_time), __FILE__, __LINE__, "Iterator index out of bounds!");
	}
}

template <typename T>
T& MatrixIterator<T>::operator*()
{
	return value();
}

template <typename T>
T& MatrixIterator<T>::value()
{
	_iterValid();
	ptrShrd<typename Matrix<T>::MatrixRow[]> matrix_data = _data.lock();
	if (_cols == 0)
	{
		time_t cur_time = time(NULL);
		auto curtime = localtime(&cur_time);
		throw IteratorColumnNumError(asctime(local_time), __FILE__, __LINE__, "Column number is zero!");
	}
	return data_ptr[_index / _cols][_index % _cols];
}

template <typename T>
T* MatrixIterator<T>::operator->()
{
	_iterValid();
	if (_cols == 0)
	{
		time_t cur_time = time(NULL);
		auto curtime = localtime(&cur_time);
		throw IteratorColumnNumError(asctime(local_time), __FILE__, __LINE__, "Column number is zero!");
	}
	ptrShrd<typename Matrix<T>::MatrixRow[]> matrix_data = _data.lock();
	return matrix_data[_index / _cols].get() + (_index % _cols);
}

template <typename T>
MatrixIterator<T>& MatrixIterator<T>::operator++() noexcept
{
	return next();
}

template <typename T>
MatrixIterator<T>& MatrixIterator<T>::next() noexcept
{
	if (_index < _cols * _rows)
		++_index;
	return *this;
}

template <typename T>
MatrixIterator<T> MatrixIterator<T>::operator++(int) noexcept
{
	MatrixIterator<T> iter(*this);
	++(*this);
	return iter;
}

template <typename T>
MatrixIterator<T>& MatrixIterator<T>::operator--() noexcept
{
	return previous;
}

template <typename T>
MatrixIterator<T>& MatrixIterator<T>::previous() noexcept
{
	if (_index < _cols * _rows)
		--_index;
	return *this;
}

template <typename T>
MatrixIterator<T> MatrixIterator<T>::operator--(int) noexcept
{
	MatrixIterator<T> iter(*this);
	--(*this);
	return iter;
}

template <typename T>
MatrixIterator<T>& MatrixIterator<T>::assign(const MatrixIterator<T>& refIterator)  noexcept
{
	_data = it._data, _index = it._index, _rows = it._rows, _cols = it._cols;
	return *this;
}

template <typename T>
MatrixIterator<T>& MatrixIterator<T>::operator=(const MatrixIterator<T>& retIterator) noexcept
{
	return assign(retIterator);
}