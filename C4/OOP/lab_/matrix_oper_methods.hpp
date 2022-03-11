template <typename T>
T &Matrix<T>::at(size_t row, size_t col) 
{
    return _data[row][col];
}

template <typename T>
const T &Matrix<T>::at(size_t row, size_t col) const 
{
    return _data[row][col];
}

template <typename T>
Matrix<T> Matrix<T>::mulElem(const T& elem) const noexcept
{
    return operator*(elem);
}

template <typename T>
Matrix<T> Matrix<T>::subMatrix(const Matrix& matrix) const
{
    return operator-(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::subElem(const T& elem) const noexcept
{
    return operator-(elem);
}

template <typename T>
Matrix<T> Matrix<T>::addMatrix(const Matrix& matrix) const
{
    return operator+(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::addElem(const T& elem) const noexcept
{
    return operator+(elem);
}

template <typename T>
Matrix<T> Matrix<T>::mulMatrix(const Matrix& matrix) const
{
    return operator*(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::subAssigMatrix(const Matrix &matrix) 
{
    return operator-=(matrix);
}

template <typename T>
Matrix<T>& Matrix<T>::subAssigElem(const T& elem) noexcept
{
    return operator-=(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::mulAssigMatrix(const Matrix &matrix) 
{
    return operator*=(matrix);
}

template <typename T>
Matrix<T>& Matrix<T>::mulAssigElem(const T& elem) noexcept
{
    return operator*=(elem);
}

template <typename T>
Matrix<T> Matrix<T>::divMatrix(const Matrix& matrix) const
{
    return operator/(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::divElem(const T& elem) const
{
    return operator/(elem);
}

template <typename T>
Matrix<T> Matrix<T>::neg()
{
    return operator-();
}

template <typename T>
Matrix<T>& Matrix<T>::addAssigMatrix(const Matrix& matrix)
{
    return operator+=(matrix);
}

template <typename T>
Matrix<T>& Matrix<T>::addAssigElem(const T& elem) noexcept
{
    return operator+=(elem);
}

template <typename T>
Matrix<T>& Matrix<T>::divAssigMatrix(const Matrix& matrix)
{
    return operator/=(matrix);
}

template <typename T>
Matrix<T>& Matrix<T>::divAssigElem(const T& elem)
{
    return operator/=(elem);
}

template <typename T>
bool Matrix<T>::checkEqual(const Matrix& matrix) const
{
    return operator==(matrix);
}

template <typename T>
bool Matrix<T>::checkUnequal(const Matrix& matrix) const
{
    return operator!=(matrix);
}