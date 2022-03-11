#pragma once

#include <exception>
#include <string>

using string = std::string;

class MatrixExceptions : public std::exception
{
public:
	// Constructor
	MatrixExceptions(const string time, const string file, const string linenum, const string err_message = "");
	// Destructor
	~MatrixExceptions() {};
	// Get string identifying exception
	virtual const char* what() const noexcept override { return _error_message.c_str(); };

protected:
	// Error message
	string _error_message;
};

class RowIndexError : public MatrixExceptions
{
public:
	RowIndexError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: RowIndexError)";
	}
};

class ZeroDivisionError : public MatrixExceptions
{
public:
	ZeroDivisionError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: ZeroDivisionError)";
	}
};

class MultiplyMatrixShapeError : public MatrixExceptions
{
public:
	MultiplyMatrixShapeError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: MultiplyMatrixShapeError)";
	}
};

class MatrixUnequalShapeError : public MatrixExceptions
{
public:
	MatrixUnequalShapeError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: MatrixUnequalShapeError)";
	}
};

class MemoryAllocationError : public MatrixExceptions
{
public:
	MemoryAllocationError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: MemoryAllocationError)";
	}
};

class IteratorMemoryError : public MatrixExceptions
{
public:
	IteratorMemoryError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: IteratorMemoryError)";
	}
};

class IteratorIndexError : public MatrixExceptions
{
public:
	IteratorIndexError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: IteratorIndexError)";
	}
};

class IteratorColumnNumError : public MatrixExceptions
{
public:
	IteratorColumnNumError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: IteratorColumnNumError)";
	}
};

class IncorrectInitializerListError : public MatrixExceptions
{
public:
	IncorrectInitializerListError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: IncorrectInitializerListError)";
	}
};

class IncorrectIdentityMatrixInitSize : public MatrixExceptions
{
public:
	IncorrectIdentityMatrixInitSize(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: IncorrectIdentityMatrixInitSize)";
	}
};

class DeterminantMatrixShapeError : public MatrixExceptions
{
public:
	DeterminantMatrixShapeError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: DeterminantMatrixShapeError)";
	}
};

class MatrixExcludeIncorrectShapeError : public MatrixExceptions
{
public:
	MatrixExcludeIncorrectShapeError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: MatrixExcludeIncorrectShapeError)";
	}
};

class MatrixInverseError : public MatrixExceptions
{
public:
	MatrixInverseError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: MatrixInverseError)";
	}
};

class RowIndexInsertError : public MatrixExceptions
{
public:
	RowIndexInsertError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: RowIndexInsertError)";
	}
};

class ColIndexInsertError : public MatrixExceptions
{
public:
	ColIndexInsertError(const string time, const string file, const string linenum, const string err_message = "") :
		MatrixExceptions(time, file, linenum, err_message)
	{
		_error_message += " (error type: ColIndexInsertError)";
	}
};