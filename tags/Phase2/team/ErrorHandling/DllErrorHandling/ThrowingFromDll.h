
#ifndef __THROWINGFROMDLL__
#define __THROWINGFROMDLL__


#ifdef EXPORT_EVERYTHING
    #define EXPORT_SYMBOLS __declspec( dllexport )
#else
    #define EXPORT_SYMBOLS __declspec( dllimport )
#endif

class EXPORT_SYMBOLS ThrowClass
{
public:
    ThrowClass(int i);
};


#endif