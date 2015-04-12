
#ifndef __QSCREENRECTANGLE__
#define __QSCREENRECTANGLE__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QPoint.h"

template<class T>
class QScreenRectangle
{
public:

    QScreenRectangle()
    {
    }

    QScreenRectangle(const QPoint<T> topLeftCorner, const QPoint<T> bottomRightCorner) : TopLeftCorner(topLeftCorner),
                                                                                         BottomRightCorner(bottomRightCorner)
    {
    }

    QScreenRectangle(const QPoint<T> topLeftCorner, const T width, const T height) : TopLeftCorner(topLeftCorner),
                                                                                     BottomRightCorner(topLeftCorner.x + width, topLeftCorner.y + height)
    {
    }

    QPoint<T> TopLeftCorner;
    QPoint<T> BottomRightCorner;
};

#endif // __QSCREENRECTANGLE__
