
#ifndef __QPOINT__
#define __QPOINT__

#include "QuimeraEngineIncludesAndUsings.h"

template<class T>
class QPoint
{
public:

    QPoint() : x(0),
               y(0)
    {
    }

    QPoint(const T positionX, const T positionY) : x(positionX), 
                                                   y(positionY)
    {
    }

    T x;
    T y;
};

#endif // __QPOINT__