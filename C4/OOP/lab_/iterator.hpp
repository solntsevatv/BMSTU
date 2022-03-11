#pragma once
#include <memory>
#include <string>
#include "exception.hpp"

// Shared pointer
template <typename T>
using SharedPtr = std::shared_ptr<T>;
// Weak pointer
template <typename T>
using WeakPtr = std::weak_ptr<T>;

// Matrix class
template <typename T>
class Matrix;

// Iterator class derived from std iterator
template <typename Type>
class Iterator: public std::iterator<std::bidirectional_iterator_tag, Type> {
public:
    // Iterator constructor
    Iterator(const Matrix<Type> &matrix, const size_t index = 0): _data(matrix._data), _index(index),
                                                                  _rows(matrix._rows), _cols(matrix._cols) {}
    // Iterator from iterator constructor
    Iterator(const Iterator& it) = default;

    // Overloading operators
    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const;
    bool operator<(Iterator const& other) const;
    
    operator bool() const;
    bool isEnd() const;
    bool isValid() const;

    // Overloading arythmetic operations for value
    Iterator<Type> operator+(const int value) const;
    Iterator<Type> operator-(const int value) const;
    Iterator<Type> &operator+=(const int value);
    Iterator<Type> &operator=(const Iterator<Type> &it);

    // Pointer operations
    Type& operator*();
    const Type& operator*() const;
    Type& value();
    const Type& value() const;

    // Overloading pointer operator
    Type* operator->();
    const Type* operator->() const;

    // Increment operations
    Iterator<Type>& operator++();
    Iterator<Type>& next();
    Iterator<Type> operator++(int);

private:
    // Index validation
    void _checkIndex(const string hint = "");
    // Check if data is valid
    void _checkValid(const string hint = "") const;
    // Data 
    WeakPtr<typename Matrix<Type>::MatrixRow[]> _data;
    // Index values
    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

// != operator overloading
template <typename T>
bool Iterator<T>::operator!=(Iterator const& other) const {
    return _index != other._index;
}

// == operator overloading
template <typename T>
bool Iterator<T>::operator==(Iterator const& other) const {
    return _index == other._index;
}

// < operator overloading
template <typename T>
bool Iterator<T>::operator<(Iterator const& other) const {
    return _index < other._index;
}   

// Check if iterator is at last element of matrix
template <typename T>
bool Iterator<T>::isEnd() const {
    return _index == _rows * _cols;
}

// Check if matrix data is valid for iteration
template <typename T>
bool Iterator<T>::isValid() const {
    return !_data.expired();
}

// Overloading + operator
template <typename T>
Iterator<T> Iterator<T>::operator+(const int value) const {
    Iterator<T> it(*this);
    if (value < 0 && it._index < static_cast<size_t>(-value))
        it._index = 0;
    else
        it._index += value;

    if (it._index < 0)
        it._index = 0;
    else if (it._index > _rows * _cols)
        it._index = _rows * _cols;

    return it;
}

// Overloading - operator
template <typename T>
Iterator<T> Iterator<T>::operator-(const int value) const {
    return operator+(-value);
}

// Overloading += operator
template <typename T>
Iterator<T>& Iterator<T>::operator+=(const int value) {
    _index += value;
    return *this;
}

// Overloading = operator
template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& it) {
    _data = it._data, _index = it._index, _rows = it._rows, _cols = it._cols;
    return *this;
}

// Check if index if valid
template <typename T>
void Iterator<T>::_checkIndex(const string hint) {
    if (_index < _rows * _cols)
        return;
    time_t cur_time = time(NULL);
    auto local_time = localtime(&cur_time);
    throw IndexError(asctime(local_time), __FILE__, __LINE__, hint);
}

// Check of data is valid
template <typename T>
void Iterator<T>::_checkValid(const string hint) const {
    if (!isValid()) { // !_data.expired()
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);
        throw MemoryError(asctime(local_time), __FILE__, __LINE__, hint);
    }
}

// Pointer operator overloading
template <typename T>
T& Iterator<T>::operator*() {
    _checkValid("Iterator points on nullptr");
    _checkIndex("Iterator doens't in data bounds, while executing operator*");
    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols][_index % _cols];
}

// Pointer method
template <typename T>
T& Iterator<T>::value() {
    return operator*();
}

// Pointer operator overloading
template <typename T>
const T& Iterator<T>::operator*() const {
    _checkValid("Iterator points on nullptr");
    _checkIndex("Iterator doens't in data bounds, while executing const operator*");
    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols][_index % _cols];
}

// Pointer operator overloading
template <typename T>
const T& Iterator<T>::value() const {
    return operator*();
}

// -> operator overloading
template <typename T>
T* Iterator<T>::operator->() {
    _checkValid("Iterator points on nullptr");
    _checkIndex("Iterator doens't in data bounds, while executing operator->");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

// -> operator
template <typename T>
const T* Iterator<T>::operator->() const {
    _checkValid("Iterator points on nullptr");
    _checkIndex("Iterator doens't in data bounds, while executing const operator->");
    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();
    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

// Increment operator realization
template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (_index < _cols * _rows)
        ++_index;
    return *this;
}

// Increment method
template <typename T>
Iterator<T>& Iterator<T>::next() {
    return operator++();
}

// Iterator increment realization
template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> it(*this);
    ++(*this);
    return it;
}

// Data validity operator
template <typename T>
Iterator<T>::operator bool() const {
    return _data.expired();
}







