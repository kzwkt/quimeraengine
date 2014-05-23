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
#include "RTTIDefinitions.h"

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
    QE_RTTI_SUPPORT_DERIVED_FROM_OBJECT(QObjectMockA);
};


// ATTRIBUTE INITIALIZATION
// --------------------------
QE_RTTI_SUPPORT_TYPE_DEFINITION(QObjectMockA);


// QObjectMockB
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockB : public virtual QObject
{
	QE_RTTI_SUPPORT_DERIVED_FROM_OBJECT(QObjectMockB);
};


// ATTRIBUTE INITIALIZATION
// --------------------------
QE_RTTI_SUPPORT_TYPE_DEFINITION(QObjectMockB);



// QObjectMockInterface
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockInterface : public virtual QObject
{
    QE_RTTI_SUPPORT_DERIVED_FROM_OBJECT(QObjectMockInterface);
};


// ATTRIBUTE INITIALIZATION
// --------------------------
QE_RTTI_SUPPORT_TYPE_DEFINITION(QObjectMockInterface);



// QObjectMockDerivedA
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in QObject tests.
/// </summary>
class QObjectMockDerivedA : public QObjectMockInterface, public QObjectMockA
{
    QE_RTTI_SUPPORT_DERIVED_FROM_2_CLASSES(QObjectMockDerivedA, QObjectMockInterface, QObjectMockA);
};


// ATTRIBUTE INITIALIZATION
// --------------------------
QE_RTTI_SUPPORT_TYPE_DEFINITION(QObjectMockDerivedA);


} //namespace Test
} //namespace Core
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QOBJECTBASEMOCK__
