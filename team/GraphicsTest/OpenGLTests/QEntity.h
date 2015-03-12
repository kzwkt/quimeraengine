
#ifndef __QENTITY__
#define __QENTITY__

#include "QuimeraEngineIncludesAndUsings.h"

class QEntity
{
public:

    class QLink
    {
    public:

        QLink() : InheritPosition(true),
                  InheritRotation(true),
                  InheritScale(true)
        {
        }

        bool InheritPosition;
        bool InheritRotation;
        bool InheritScale;
    };

public:

    void SetPosition(const QVector3 &position)
    {
        this->LocalPosition.x = position.x;
        this->LocalPosition.y = position.y;
        this->LocalPosition.z = position.z;
    }

    void SetPosition(const QVector4 &position)
    {
        this->LocalPosition = position;
    }

    void SetOrientation(const QQuaternion &orientation)
    {
        this->LocalOrientation = orientation;
    }

    void SetScale(const QVector3 &scale)
    {
        this->LocalScale = scale;
    }

    void Move(const QVector3 &movement)
    {
        this->LocalPosition += movement;
    }

    void Rotate(const QQuaternion &rotation)
    {
        this->LocalOrientation * rotation;
    }

    void RotatePitch(const float_q fAngle)
    {
        this->LocalOrientation *= QQuaternion(fAngle, SQFloat::_0, SQFloat::_0);
    }

    void RotateYaw(const float_q fAngle)
    {
        this->LocalOrientation *= QQuaternion(SQFloat::_0, fAngle, SQFloat::_0);
    }

    void RotateRoll(const float_q fAngle)
    {
        this->LocalOrientation *= QQuaternion(SQFloat::_0, SQFloat::_0, fAngle);
    }

    void Scale(const QVector3 &scale)
    {
        this->LocalScale *= scale;
    }

    QTransformationMatrix<QMatrix4x4> GetTransformationMatrix() const
    {
        return QTransformationMatrix<QMatrix4x4>(this->LocalPosition, this->LocalOrientation, this->LocalScale);
    }

public:

    QVector4 LocalPosition;
    QQuaternion LocalOrientation;
    QVector3 LocalScale;
    QLink Link;

};


#endif // __QENTITY__