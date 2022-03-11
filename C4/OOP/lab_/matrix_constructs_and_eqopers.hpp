// Check if ptr is valid
template <typename T>
static void _checkPtr(T ptr) 
{
    if (!ptr) {
        time_t cur_time = time(NULL);
        auto curtime = localtime(&cur_time);
        throw PointerError(asctime(curtime), __FILE__, __LINE__, "nullptr as a ptr of c-matrix");
    }
}

// Constructor for rows cols matrix
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : MatrixBase(rows, columns) 
{
    _data = _allocMemory(rows, columns);
}

// Constructor for rows cols with filler
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T& filler) : MatrixBase(rows, columns) 
{
    _data = _allocMemory(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = filler;
}

// Constructor for existing matrix copy
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T **matrix): MatrixBase(rows, columns) 
{
    _checkPtr(matrix);
    _data = _allocMemory(rows, columns);
    for (size_t i = 0; i < rows; ++i)
    {
        _checkPtr(matrix[i]);
        for (size_t j = 0; j < columns; ++j)
            _data[i][j] = matrix[i][j];
    }
}

// Constructor from const matrix
template <typename T>
Matrix<T>::Matrix(const Matrix &matrix): MatrixBase(matrix._rows, matrix._cols) 
{
    _data = _allocMemory(matrix._rows, matrix._cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
}

// Constructor from matrix
template <typename T>
Matrix<T>::Matrix(Matrix &&matrix): MatrixBase(matrix._rows, matrix._cols) 
{
    _data = matrix._data;
}

// Assign operator overloading for const matrix
template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix) 
{
    _data = _allocMemory(matrix._rows, matrix._cols);
    _rows = matrix._rows, _cols = matrix._cols;
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
    return *this;
}

// Assign operator overloading
template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&matrix) 
{
    _rows = matrix._rows, _cols = matrix._cols;
    _data = matrix._data;
    return *this;
}

// Initializer list
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list) {
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto& ilist : init_list)
        if (ilist.size() != cols) {
            time_t cur_time = time(NULL);
            auto curtime = localtime(&cur_time);
            throw InitializerError(asctime(curtime), __FILE__, __LINE__, "Bad initializer list");
        }

    _data = _allocMemory(rows, cols);
    _rows = rows;
    _cols = cols;
    size_t i = 0;
    for (const auto& ilist : init_list)
        for (const auto& elem : ilist)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
}

// Initializer list operator
template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T> > init_list) {
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto& ilist : init_list)
        if (ilist.size() != cols) {
            time_t cur_time = time(NULL);
            auto curtime = localtime(&cur_time);
            throw InitializerError(asctime(curtime), __FILE__, __LINE__, "Bad initializer list");
        }

    resize(rows, cols);
    size_t i = 0;
    for (const auto& ilist : init_list)
        for (const auto& elem : ilist)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
    return *this;
}
