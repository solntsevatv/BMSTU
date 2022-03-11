#include "matrix_const_iterator.hpp"

template <typename T>
void MatrixConstIterator<T>::_iterValid()
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
bool MatrixConstIterator<T>::equal(MatrixConstIterator const& other) const noexcept
{
	return _index == other._index;
}

template <typename T>
bool MatrixConstIterator<T>::operator!=(MatrixConstIterator const& other) const noexcept
{
	return equal(other);
}

template <typename T>
bool MatrixConstIterator<T>::unequal(MatrixConstIterator const& other) const noexcept
{
	return _index != other._index;
}

template <typename T>
bool MatrixConstIterator<T>::operator!=(MatrixConstIterator const& other) const noexcept
{
	return unequal(other);
}

template <typename T>
bool MatrixConstIterator<T>::lesser(MatrixConstIterator const& other) const noexcept
{
	return _index < other._index;
}

template <typename T>
bool MatrixConstIterator<T>::operator<(MatrixConstIterator const& other) const noexcept
{
	return lesser(other);
}

template <typename T>
bool MatrixConstIterator<T>::greater(MatrixConstIterator const& other) const noexcept
{
	return _index > other._index;
}

template <typename T>
bool MatrixConstIterator<T>::operator>(MatrixConstIterator const& other) const noexcept
{
	return greater(other);
}

// Index checkups
template <typename T>
bool MatrixConstIterator<T>::valid() const noexcept
{
	return !_data.expired();
}

template <typename T>
bool MatrixConstIterator<T>::end() const noexcept
{
	return _index == _rows * _cols;
}

template <typename T>
bool MatrixConstIterator<T>::start() const noexcept
{
	return _index == 0;
}

template <typename T>
MatrixConstIterator<T>::operator bool() const noexcept
{
	return _data.expired();
}

template <typename T>
const T& MatrixConstIterator<T>::value() const
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
const T& MatrixConstIterator<T>::operator*() const
{
	return value();
}

template <typename T>
const T* MatrixConstIterator<T>::operator->() const
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
MatrixConstIterator<T>& MatrixConstIterator<T>::operator++() const noexcept
{
	return next();
}

template <typename T>
MatrixConstIterator<T>& MatrixConstIterator<T>::next() const noexcept
{
	if (_index < _cols * _rows)
		++_index;
	return *this;
}

template <typename T>
MatrixConstIterator<T> MatrixConstIterator<T>::operator++(int) const noexcept
{
	MatrixConstIterator<T> iter(*this);
	++(*this);
	return iter;
}

template <typename T>
MatrixConstIterator<T>& MatrixConstIterator<T>::operator--() const noexcept
{
	return previous;
}

template <typename T>
MatrixConstIterator<T>& MatrixConstIterator<T>::previous() const noexcept
{
	if (_index < _cols * _rows)
		--_index;
	return *this;
}

template <typename T>
MatrixConstIterator<T> MatrixConstIterator<T>::operator--(int) const noexcept
{
	MatrixConstIterator<T> iter(*this);
	--(*this);
	return iter;
}