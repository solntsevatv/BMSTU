#include "matrix.hpp"

/*
    Matrix constructors
*/
// Standart constructor
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : MatrixBase(rows, columns)
{
    _data = _allocData(rows, columns);
}

// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix& matrix) : MatrixBase(matrix._rows, matrix._rows)
{
    _data = _allocData(matrix._rows, matrix._cols);

    for (size_t i = 0; i < matrix._rows; i++)
        for (size_t j = 0; j < matrix._cols; j++)
            _data[i][j] = matrix[i][j];
}

// Constructor with filler
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T& filler) : MatrixBase(rows, columns)
{
    _data = _allocData(rows, columns);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            _data[i][j] = filler;
}

// C-matrix constructor
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T** matrix) : MatrixBase(rows, columns)
{
    _data = _allocData(rows, columns);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            _data[i][j] = matrix[i][j];
}

// C-matrix copy constructor
template <typename T>
Matrix<T>::Matrix(Matrix&& matrix) : MatrixBase(matrix._rows, matrix._cols)
{
    _data = matrix._data;
}

// Initializer list matrix constructor
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > init_list)
{
    auto iterator = init_list.begin();

    size_t rows = init_list.size();
    size_t cols = iterator->size();

    // check cols
    for (const auto& col_list : init_list)
    {
        if (col_list, size() != cols)
        {
            time_t time_current = time(NULL);
            auto time_local = localtime(&time_current);
            throw IncorrectInitializerListError(asctime(local_time), __FILE__, __LINE__, "Incorrect initializer list");
        }
    }

    _data = _allocData(rows, cols);
    _rows = rows;
    _cols = cols;

    size_t i = 0;
    for (const auto& col_list : init_list)
    {
        for (const auto& element : col_list)
        {
            _data[i / cols][i % cols] = element;
            ++i;
        }
    }
}

// Create identity matrix
template <typename T>
Matrix<T> Matrix<T>::IdentityMatrix(size_t size)
{
    if (size == 0)
    {
        time_t time_current = time(NULL);
        auto time_local = localtime(&time_current);
        throw IncorrectInitializerListError(asctime(local_time), __FILE__, __LINE__, "Identity matrix size can't be zero");
    }

    _data = _allocData(size, size);

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i == j)
                _data[i][j] = 1;
            else
                _data[i][j] = 0;
        }
    }
}

/*
    Iterators section
*/

// Iterators
template <typename T>
MatrixIterator<T> Matrix<T>::begin()
{
    return MatrixIterator<T>(*this, 0);
}

template <typename T>
MatrixIterator<T> Matrix<T>::end()
{
    return MatrixIterator<T>(*this, _rows * _cols);
}

// Constant iterators
template <typename T>
MatrixConstIterator<T> Matrix<T>::begin() const
{
    return MatrixConstIterator<T>(*this, 0);
}

template <typename T>
MatrixConstIterator<T> Matrix<T>::end() const
{
    return MatrixConstIterator<T>(*this, _rows * _cols);
}

// C-iterators
template <typename T>
MatrixConstIterator<T> Matrix<T>::cbegin() const
{
    return MatrixConstIterator<T>(*this, 0);
}

template <typename T>
MatrixConstIterator<T> Matrix<T>::cend() const
{
    return MatrixConstIterator<T>(*this, _rows * _cols);
}

/*
    Bool operatinons
*/

// Matrix equality overload method
template <typename T>
bool Matrix<T>::equal(const Matrix& matrix) const
{
    bool isEqual = false;

    if ((_rows == matrix._rows) && (_cols == matrix._cols))
    {
        for (size_t i = 0; i < _rows && isEqual; i++)
            for (size_t j = 0; j < _cols && isEqual; j++)
                isEqual = _data[i][j] == matrix[i][j];
    }

    return isEqual;
}

// Matrix equality overload operator
template <typename T>
bool Matrix<T>::operator==(const Matrix& matrix) const
{
    return equal(matrix);
}

// Matrix inequality overload method
template <typename T>
bool Matrix<T>::unequal(const Matrix& matrix) const
{
    bool isUnequal = true;

    if ((_rows == matrix._rows) && (_cols == matrix._cols))
    {
        for (size_t i = 0; i < _rows && isUnequal; i++)
            for (size_t j = 0; j < _cols && isUnequal; j++)
                isUnequal = _data[i][j] != matrix[i][j];
    }

    return isUnequal;
}

// Matrix inequality overloda operator
template <typename T>
bool Matrix<T>::operator!=(const Matrix& matrix) const
{
    return unequal(matrix);
}

/*
    Pointer operators
*/

// Get pointer for elemet at row col position
template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col)
{
    return _data[row][col];
}

// Matrix get row by index operator
template <typename T>
Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row)
{
    return _data[row];
}

// Get matrix element at position
template <typename T>
T& Matrix<T>::at(size_t row, size_t col)
{
    return _data[row][col];
}

// Get pointer for elemet at row col position
template <typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const
{
    return _data[row][col];
}

// Matrix get row by index operator
template <typename T>
const Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row) const
{
    return _data[row];
}

// Get matrix element at position
template <typename T>
const T& Matrix<T>::at(size_t row, size_t col) const
{
    return _data[row][col];
}

/*
    Standart matrix methods
*/

// Check if square
template <typename T>
bool Matrix<T>::square() const
{
    return _rows == _cols;
}

template <typename T>
static void _excludeColnRowByIndex(Matrix<T>& dst, const Matrix<T>& src, size_t ex_i, size_t ex_j)
{
    if (dst.Rows() != src.Rows() - 1 || dst.Cols() != src.Cols() - 1)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw MatrixExcludeIncorrectShapeError(asctime(curtime), __FILE__, __LINE__, "Source matrix sizes must be by one lower than destinations");
    }

    size_t row;
    size_t col;

    for (size_t i = 0; i < src.Rows() - 1; ++i)
    {
        for (size_t j = 0; j < src.Cols() - 1; ++j)
        {
            row = i;
            col = j;
            if (i >= ex_i)
                row = i + 1;
            if (j >= ex_j)
                col = j + 1;

            dst[i][j] = src[row][col];
        }
    }
}

template <typename T>
static T _determinant(const Matrix<T>& matr)
{
    if (matr.Rows() == 1)
        return matr[0][0];

    if (matr.Rows() == 2)
        return matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];

    Matrix<T> temp(matr.Rows() - 1, matr.Cols() - 1);
    T result = {};

    for (size_t i = 0; i < matr.Rows(); ++i)
    {
        _excludeColnRowByIndex(temp, matr, 0, i);
        T minor = _determinant(temp);

        if (i & 1)
            minor = -minor;

        result += minor * matr[0][i];
    }

    return result;
}

// Count determinant
template <typename T>
T Matrix<T>::determinant() const
{
    if (!square())
    {
        time_t time_current = time(NULL);
        auto time_local = localtime(&time_current);
        throw MatrixUnequalShapeError(asctime(local_time), __FILE__, __LINE__, "To count determinant matrix must be square");
    }

    return _determinant(*this);
}

// Transpose matrix
template <typename T>
void Matrix<T>::transpose()
{
    auto temp = _allocData(_cols, _rows);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[j][i] = _data[i][j];
        }
    }
    _data = temp;

    std::swap(_rows, _cols);
}

// Inverse matrix
template <typename T>
void Matrix<T>::inverse()
{
    T matr_det = determinant();

    if (!square() || !matr_det)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw MatrixInverseError(asctime(curtime), __FILE__, __LINE__, "Matrix must be square, determinant should be > 0");
    }

    T val = {};

    Matrix<T> result_matr(_rows, _cols);
    Matrix<T> temp_matr(_rows, _cols);
    
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            _excludeColnRowByIndex(temp_matr, *this, i, j);
            val = temp_matr.determinant() / matr_det;

            if ((i + j) & 1)
                val = -val;

            result_matr[j][i] = val;
        }
    }

    *this = result_matr;
}

/*
    Math operators and methods section
*/

// Adds matrix to matrix element by element
template <typename T>
Matrix<T> Matrix<T>::add(const Matrix& matrix) const
{
    _validateSizeEqual(matrix);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] + matrix[i][j];
        }
    }

    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& matrix) const
{
    return add(matrix);
}

// Add elem to each element of matrix
template <typename T>
Matrix<T> Matrix<T>::addElem(const T& elem) const
{
    Matrix<T> temp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] + elem;
        }
    }

    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T& elem) const
{
    return addElem(elem);
}

// Substracts matrix element by element
template <typename T>
Matrix<T> Matrix<T>::sub(const Matrix& matrix) const
{
    _validateSizeEqual(matrix);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] + matrix[i][j];
        }
    }

    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& matrix) const
{
    return sub(matrix);
}

// Substract element from matrix element by element
template <typename T>
Matrix<T> Matrix<T>::subElem(const T& elem) const
{
    Matrix<T> temp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] + elem;
        }
    }

    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T& elem) const
{
    return subElem(elem);
}

// Dot matrix
template <typename T>
Matrix<T> Matrix<T>::dot(const Matrix& matrix) const
{
    _validateSizeMatrMult(matrix);

    Matrix<T> result(_rows, matrix._cols);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < matrix._cols; ++j)
        {
            for (size_t k = 0; k < _cols; ++k)
            {
                result[i][j] += _data[i][k] * matrix[k][j];
            }
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& matrix) const
{
    return dot(matrix);
}

// Multiply matrix element by element
template <typename T>
Matrix<T> Matrix<T>::mulElem(const T& elem) const
{
    Matrix<T> temp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] * elem;
        }
    }

    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& elem) const
{
    return mulElem(elem);
}

// Multiply matrix by matrix element by element
template <typename T>
Matrix<T> Matrix<T>::mulElem(const Matrix& matrix) const
{
    _validateSizeEqual(matrix);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] * matrix[i][j];
        }
    }

    return temp;
}

// Divide matrix by matrix rules
template <typename T>
Matrix<T> Matrix<T>::div(const Matrix& matrix) const
{
    Matrix<T> temp(matrix);
    temp.inverse();
    return dot(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix& matrix) const
{
    return div(matrix);
}

// Divide matrix element by element
template <typename T>
Matrix<T> Matrix<T>::divElem(const T& elem) const
{
    Matrix<T> temp(matrix);
    temp.inverse();
    return temp * elem;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& elem) const
{
    return divElem(elem);
}

// Divide matrix by matrix element by element
template <typename T>
Matrix<T> Matrix<T>::divElem(const Matrix& matrix) const
{
    _validateSizeEqual(matrix);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            if (matrix[i][j] == 0)
            {
                time_t cur_time = time(NULL);
                auto curtime = localtime(&cur_time);
                throw ZeroDivisionError(asctime(curtime), __FILE__, __LINE__, "Zero division error");
            }

            temp[i][j] = _data[i][j] / matrix[i][j];
        }
    }

    return temp;
}
// Negative matrix 
template <typename T>
Matrix<T> Matrix<T>::negative()
{
    Matrix<T> result(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            result[i][j] = -_data[i][j];
        }
    }

    return result;
}

// Negative matrix operator
template <typename T>
Matrix<T> Matrix<T>::operator-()
{
    return negative();
}

/*
    Arithmetic assign operations
*/

// Add matrix and assign
template <typename T>
Matrix<T>& Matrix<T>::addAssigMatrix(const Matrix& matrix)
{
    _validateSizeEqual(matrix);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            _data[i][j] += matrix[i][j];
        }
    }

    return *this;
}

// Add matrix and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& matrix)
{
    return addAssigMatrix(matrix);
}

// Add element and assign
template <typename T>
Matrix<T>& Matrix<T>::addAssigElem(const T& elem)
{
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            _data[i][j] += elem;
        }
    }

    return *this;
}

// Add element and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& elem)
{
    return addAssigElem(elem);
}

// Substract matrix and assign 
template <typename T>
Matrix<T>& Matrix<T>::subAssigMatrix(const Matrix& matrix)
{
    _validateSizeEqual(matrix);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            _data[i][j] -= matrix[i][j];
        }
    }

    return *this;
}

// Substract matrix and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& matrix)
{
    return subAssigMatrix(matrix);
}

// Substract element and assign
template <typename T>
Matrix<T>& Matrix<T>::subAssigElem(const T& elem)
{
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            _data[i][j] -= elem;
        }
    }

    return *this;
}

// Substract element and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& elem)
{
    return subAssigElem(elem);
}

// Multiply by matrix and assign
template <typename T>
Matrix<T>& Matrix<T>::mulAssigMatrix(const Matrix& matrix)
{
    _validateSizeMatrMult(matrix);

    Matrix<T> result(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            for (size_t k = 0; k < _rows; ++k)
            {
                tmp[i][j] += _data[i][k] + matrix[k][j];
            }
        }
    }

    *this = result;
    return *this;
}

// Multiply by matrix and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& matrix)
{
    return mulAssigMatrix(matrix);
}

// Multiply by element and assign 
template <typename T>
Matrix<T>& Matrix<T>::mulAssigElem(const T& elem)
{
    Matrix<T> temp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] * elem;
        }
    }

    *this = result;
    return *this;
}

// Multiply by element and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& elem)
{
    return mulAssigElem(elem);
}

// Multiply element by element and assign
template <typename T>
Matrix<T>& Matrix<T>::mulAssigElem(const Matrix& matrix)
{
    _validateSizeEqual(matrix);

    Matrix<T> temp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            temp[i][j] = _data[i][j] * matrix[i][j];
        }
    }

    *this = result;
    return *this;
}

// Divide by matrix and assign
template <typename T>
Matrix<T>& Matrix<T>::divAssigMatrix(const Matrix& matrix)
{
    Matrix<T> result = operator/(matrix);
    *this = result;
    return *this;
}

// Divide by matrix and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix& matrix)
{
    return divAssigMatrix(matrix);
}

// Divide by element and assign
template <typename T>
Matrix<T>& Matrix<T>::divAssigElem(const T& elem)
{
    Matrix<T> result = operator/(elem);
    *this = result;
    return *this;
}

// Divide by element and assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& elem)
{
    return divAssigElem(elem);
}

// Divide by element and assign (simple)
template <typename T>
Matrix<T>& Matrix<T>::divAssigElem(const Matrix& matrix)
{
    Matrix<T> result = divElem(matrix);
    *this = result;
    return *this;
}

/*
    Assign methods and operators
*/

// Const assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& matrix)
{
    _data = _allocData(matrix._rows, matrix._cols);
    _rows = matrix._rows;
    _cols = matrix._cols;

    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            _data[i][j] = matrix[i][j];
        }
    }

    return *this;
}

// Assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& matrix)
{
    _rows = matrix._rows;
    _cols = matrix._cols;

    _data = matrix._data;

    return *this;
}

// Initializer list assign operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T> > init_list)
{
    size_t rows = init_list.size();
    size_t cols = iter->size();

    auto iter = init_list.begin();
    
    for (const auto& col_list : init_list)
    {
        if (col_list.size() != cols)
        {
            time_t cur_time = time(NULL);
            auto curtime = localtime(&cur_time);
            throw IncorrectInitializerListError(asctime(curtime), __FILE__, __LINE__, "Incorrect initializer list");
        }
    }

    resize(rows, cols);
    
    size_t = 0;

    for (const auto& col_list : init_list)
    {
        for (const auto& element : init_list)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
    }

    return *this;
}

/*
    Filler methods
*/

// Fill with value from start to end
template <typename T>
void Matrix<T>::fill(MatrixIterator<T> start, const MatrixIterator<T>& end, const T& value)
{
    for (auto iterator = start; iterator < end; ++iterator)
        *iterator = value;
}

// Fill form constartn source from start to end
template <typename T>
void Matrix<T>::fill(MatrixIterator<T> start, MatrixConstIterator<T> src_start, const MatrixConstIterator<T>& src_end)
{
    auto src_iter = src_start;
    auto iter = start;

    while (!iter.end() && src_it < src_end)
    {
        *iter = *src_iter;
        ++iter;
        ++src_iter;
    }
}

// Fill from source from start to end
template <typename T>
void Matrix<T>::fill(MatrixIterator<T> start, MatrixIterator<T> src_start, const MatrixIterator<T>& src_end)
{
    auto src_iter = src_start;
    auto iter = start;

    while (!iter.end() && src_iter < src_end)
    {
        *iter = *src_iter;
        ++iter;
        ++src_iter;
    }
}

/*
    Resize operations
*/

// Resize matrix
template <typename T>
void Matrix<T>::resize(size_t rows, size_t cols, const T& filler)
{
    if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
    {
        rows = 0;
        cols = 0;
    }

    auto buff = _allocData(rows, cols);

    for (size_t i = 0; i < std::min(_rows, rows); ++i)
    {
        for (size_t j = 0; j < std::min(_cols, cols); ++j)
            buff[i][j] = _data[i][j];
        for (size_t j = _cols; j < cols; ++j)
            buff[i][j] = filler;
    }

    for (size_t i = _rows; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            buff[i][j] = filler;

    _rows = rows;
    _cols = cols;

    _data = buff;
}

// Resize by rows
template <typename T>
void Matrix<T>::resizeRows(size_t new_size, const T& filler)
{
    resize(new_size, _cols, filler);
}

// Resize by cols
template <typename T>
void Matrix<T>::resizeCols(size_t new_size, const T& filler)
{
    resize(_rows, new_size, filler);
}

/*
    Insert methods
*/

// Insert row
template <typename T>
void Matrix<T>::insertRow(size_t pos, const T& filler)
{
    if (pos > _rows)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw RowIndexInsertError(asctime(curtime), __FILE__, __LINE__, "Incorrect row insertion position");
    }

    resizeRows(_rows + 1);
    fill(end() - static_cast<int>(_cols), end(), filler);
    _relocateRow(_row - 1, pos);
}

// Instert column
template <typename T>
void Matrix<T>::insertCol(size_t pos, const T& filler)
{
    if (pos > _cols)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw ColIndexInsertError(asctime(curtime), __FILE__, __LINE__, "Incorrect column insertion position");
    }

    resizeCols(_cols + 1);
    for (size_t i = 0; i < _rows; i++)
        _data[i][_cols - 1] = filler;
    _relocateCol(_cols - 1, pos);
}

/*
    Remove methods
*/

// Remove row
template <typename T>
void Matrix<T>::removeRow(size_t index)
{
    if (index > _rows - 1)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw RowIndexInsertError(asctime(curtime), __FILE__, __LINE__, "Incorrect row deletion position");
    }

    auto buff = _allocData(_rows - 1, _cols);

    size_t src_index = 0;
    size_t dst_index = 0;

    while (src_index < _rows)
    {
        if (src_index != index)
        {
            for (size_t i = 0; i < _cols; ++i)
                buff[dst_index][i] = _data[src_index];
            ++dst_index;
        }
        ++src_index;
    }
    --_rows;
    _data = buff;
}

// Remove col
template <typename T>
void Matrix<T>::removeCol(size_t index)
{
    if (index > _cols - 1)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw ColIndexInsertError(asctime(curtime), __FILE__, __LINE__, "Incorrect column deletion position");
    }

    auto buff = _allocData(_rows, _cols - 1);

    size_t src_index = 0;
    size_t dst_index = 0;

    while (src_index < _cols)
    {
        if (src_index != index)
        {
            for (size_t i = 0; i < _rows; ++i)
                buff[i][dst_index] = _data[i][src_index];
            ++dst_index;
        }
        ++src_index;
    }
    --_cols;

    _data = buff;
}

/*
    Private matrix methods
*/
// Relocate row from src to dst inside matrix
template <typename T>
void Matrix<T>::_relocateRow(size_t src, size_t dst)
{
    MatrixRow buff = data[src];
    size_t index = src;
    while (src > dst)
    {
        _data[index] = _data[index - 1];
        index--;
    }

    while (src < dst)
    {
        _data[index] = _data[index + 1];
        index++;
    }

    _data[dst] = buff;
}

// Relocate column from src to dst inside matrix
template <typename T>
void Matrix<T>::_relocateCol(size_t src, size_t dst)
{
    size_t index = src;
}

// Memory allocator
template <typename T>
ptrShrd<typename Matrix<T>::MatrixRow[]> Matrix<T>::_allocData(size_t rows, size_t cols)
{
    ptrShrd<T[]> data = nullptr;
    try {
        data.reset(new MatrixRow[rows]);
        for (size_t i = 0; i < rows; i++)
            data[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc& errs)
    {
        time_t time_current = time(NULL);
        auto time_local = localtime(&time_current);
        throw MemoryAllocationError(asctime(local_time), __FILE__, __LINE__, "Matrix allocation error");
    }
    return data;
}

/*
    Matrix row methods
*/
// Get element by index method
template <typename T>
T& Matrix<T>::MatrixRow::atRow(size_t index)
{
    if (index >= _size)
    {
        time_t time_current = time(NULL);
        auto time_local = localtime(&time_current);
        throw RowIndexError(asctime(local_time), __FILE__, __LINE__, "Incorrect row");
    }
    return _data[index];
}

// Get element by index operator
template <typename T>
T& Matrix<T>::MatrixRow::operator[](size_t index)
{
    return atRow(index);
}

// Get const raw element by index
template <typename T>
const T& Matrix<T>::MatrixRow::operator[](size_t index) const
{
    return atRow(index);
}

// Reset row with new values
template <typename T>
void Matrix<T>::MatrixRow::reset(T* data, const size_t size)
{
    _size = size;
    _data.reset(data);
}

// Reset row completly
template <typename T>
void Matrix<T>::MatrixRow::reset()
{
    _size = 0;
    _data.reset();
}

template <typename T>
void Matrix<T>::_validateSizeEqual(const Matrix<T>& matrix) const
{
    if (_rows != matrix._rows || _cols != matrix._cols)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw MatrixUnequalShapeError(asctime(curtime), __FILE__, __LINE__, "Different matrix sizes");
    }
}

template <typename T>
void Matrix<T>::_validateSizeMatrMult(const Matrix<T>& matrix) const
{
    if (_cols != matrix._rows)
    {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time)
        throw MultiplyMatrixShapeError(asctime(curtime), __FILE__, __LINE__, "Matrix multiplication elements sizes error");
    }
}