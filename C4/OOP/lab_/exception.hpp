#pragma once
#include <exception>
#include <string>

using string = std::string;

class ExceptionMatrix: public std::exception 
{
protected:
    string _errmsg;
public:
    ExceptionMatrix(const string time_info, const string file_info, const int line_info, 
                    const string errmsg = "No error message");
    virtual ~ExceptionMatrix() {};
    virtual const char *what() const noexcept override 
    {
        return _errmsg.c_str();
    };
};

ExceptionMatrix::ExceptionMatrix(const string time_info, const string file_info, const int line_info,
    const string errmsg)
{
    _errmsg = "\nFile: " + file_info + "\nLine: " + std::to_string(line_info) + "\nTime: " + time_info + "Message: " + errmsg;
}

class PointerError : public ExceptionMatrix
{
public:
    PointerError(const string time_info, const string file_info, const int line_info,
        const string errmsg = "No error message") :
        ExceptionMatrix(time_info, file_info, line_info, errmsg)
    {
        _errmsg += " (error type: PointerError)";
    }
};

class InvalidShapeError : public ExceptionMatrix
{
public:
    InvalidShapeError(const string time_info, const string file_info, const int line_info,
        const string errmsg = "No error message") :
        ExceptionMatrix(time_info, file_info, line_info, errmsg)
    {
        _errmsg += " (error type: InvalidShape)";
    }
};

class InitializerError : public ExceptionMatrix
{
public:
    InitializerError(const string time_info, const string file_info, const int line_info,
        const string errmsg = "No error message") :
        ExceptionMatrix(time_info, file_info, line_info, errmsg)
    {
        _errmsg += " (error type: InitializerError)";
    }
};

class MemoryAllocationError : public ExceptionMatrix
{
public:
    MemoryAllocationError(const string time_info, const string file_info, const int line_info,
        const string errmsg = "No error message") :
        ExceptionMatrix(time_info, file_info, line_info, errmsg)
    {
        _errmsg += " (error type: MemoryAllocationError)";
    }
};

class MemoryError : public ExceptionMatrix
{
public:
    MemoryError(const string time_info, const string file_info, const int line_info,
        const string errmsg = "No error message") :
        ExceptionMatrix(time_info, file_info, line_info, errmsg)
    {
        _errmsg += " (error type: MemoryError)";
    }
};

class IndexError : public ExceptionMatrix
{
public:
    IndexError(const string time_info, const string file_info, const int line_info,
        const string errmsg = "No error message") :
        ExceptionMatrix(time_info, file_info, line_info, errmsg)
    {
        _errmsg += " (error type: IndexError)";
    }
};

class ZeroDivisionError : public ExceptionMatrix
{
public: ZeroDivisionError(const string time_info, const string file_info, const int line_info,
    const string errmsg = "No error message") :
    ExceptionMatrix(time_info, file_info, line_info, errmsg)
{
    _errmsg += " (error type: ZeroDivisionError)";
}
};