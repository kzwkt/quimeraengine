//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __QOBJECTBASEMOCK__
#define __QOBJECTBASEMOCK__

#include "QObject.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QType;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Core    
{
namespace Test
{
    
// These classes are used to test some features of QObject
//
//                       ____QObject____
//                        /     \      \
//                       /       \      \
//   QObjectInterfaceMock  QObjectMockA  QObjectMockB
//                 \             /
//                  \           /
//               QObjectMockDerivedA


// QObjectMockA
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockA : public virtual QObject
{

	// PROPERTIES
	// ---------------
public:

    static const QType* GetTypeClass()
    {
        return QObjectMockA::OBJECT_TYPE;
    }

    virtual const QType* GetTypeObject() const
    {
        return QObjectMockA::OBJECT_TYPE;
    }

protected:

    virtual bool OverrideIs(const QType* pType) const
    {
        return QObjectMockA::OBJECT_TYPE == pType;
    }


	// ATTRIBUTES
	// ---------------
private:

    static const QType* OBJECT_TYPE;
};


// ATTRIBUTE INITIALIZATION
// --------------------------
const QType* QObjectMockA::OBJECT_TYPE = new QType(QE_L("QObjectMockA"));


// QObjectMockB
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockB : public virtual QObject
{

	// PROPERTIES
	// ---------------
public:

    static const QType* GetTypeClass()
    {
        return QObjectMockB::OBJECT_TYPE;
    }

    virtual const QType* GetTypeObject() const
    {
        return QObjectMockB::OBJECT_TYPE;
    }

protected:

    virtual bool OverrideIs(const QType* pType) const
    {
        return QObjectMockB::OBJECT_TYPE == pType;
    }


	// ATTRIBUTES
	// ---------------
private:

    static const QType* OBJECT_TYPE;
};


// ATTRIBUTE INITIALIZATION
// --------------------------
const QType* QObjectMockB::OBJECT_TYPE = new QType(QE_L("QObjectMockB"));



// QObjectMockInterface
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockInterface : public virtual QObject
{

	// PROPERTIES
	// ---------------
public:

    static const QType* GetTypeClass()
    {
        return QObjectMockInterface::OBJECT_TYPE;
    }

    virtual const QType* GetTypeObject() const
    {
        return QObjectMockInterface::OBJECT_TYPE;
    }

protected:

    virtual bool OverrideIs(const QType* pType) const
    {
        return QObjectMockInterface::OBJECT_TYPE == pType;
    }


	// ATTRIBUTES
	// ---------------
private:

    static const QType* OBJECT_TYPE;
};


// ATTRIBUTE INITIALIZATION
// --------------------------
const QType* QObjectMockInterface::OBJECT_TYPE = new QType(QE_L("QObjectMockInterface"));



// QObjectMockDerivedA
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockDerivedA : public QObjectMockInterface, public QObjectMockA
{

	// PROPERTIES
	// ---------------
public:

    static const QType* GetTypeClass()
    {
        return QObjectMockDerivedA::OBJECT_TYPE;
    }

    virtual const QType* GetTypeObject() const
    {
        return QObjectMockDerivedA::OBJECT_TYPE;
    }

protected:

    virtual bool OverrideIs(const QType* pType) const
    {
        return QObjectMockDerivedA::OBJECT_TYPE == pType ||
                 QObjectMockInterface::OverrideIs(pType) ||
                 QObjectMockA::OverrideIs(pType);
    }


	// ATTRIBUTES
	// ---------------
private:

    static const QType* OBJECT_TYPE;
};


// ATTRIBUTE INITIALIZATION
// --------------------------
const QType* QObjectMockDerivedA::OBJECT_TYPE = new QType(QE_L("QObjectMockDerivedA"));


} //namespace Test
} //namespace Core
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QOBJECTBASEMOCK__
