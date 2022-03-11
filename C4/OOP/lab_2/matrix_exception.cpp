#include "matrix_exception.hpp"

MatrixExceptions::MatrixExceptions(const string time, const string file, const string linenum, const string err_message)
{
	_error_message = "Exception info:\ntime:" + time + "\nfile:" + file, "\nline:" + linenum + "\nerror:" + err_message;
}