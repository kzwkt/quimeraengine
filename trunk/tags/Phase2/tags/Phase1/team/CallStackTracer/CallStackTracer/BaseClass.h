#ifndef __BASECLASS__
#define __BASECLASS__

#include <string>

class BaseClass
{
public:

    BaseClass()
    {
    }

    static std::string GetTypeClass()
    {
        return "BaseClass";
    }

    virtual std::string GetType()
    {
        return "BaseClass";
    }

    virtual std::string ToString()
    {
        return "any";
    }

    template<class T>
    T* As()
    {
        return (T*)this;
    }
};

#endif // __BASECLASS__