#ifndef EX1_EXCEPTION_H
#define EX1_EXCEPTION_H
#include <stdexcept>

class GeneralException: public std::logic_error
{
public:
    virtual ~GeneralException() {}
    explicit GeneralException(const std::string& what) :std::logic_error(what){};
};

class InvalidInput: GeneralException
{
public:
    explicit InvalidInput():GeneralException(""){}
};

class AllocationError: GeneralException
{
public:
    explicit AllocationError():GeneralException(""){}
};

class FailureError: GeneralException
{
public:
    explicit FailureError():GeneralException(""){}
};



#endif //EX1_EXCEPTION_H
