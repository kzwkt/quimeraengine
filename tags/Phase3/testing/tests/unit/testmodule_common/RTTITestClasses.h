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

#ifndef __RTTITESTCLASSES__
#define __RTTITESTCLASSES__

#include "RTTIDefinitions.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QType;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common    
{
namespace Test
{
    
// These classes are used to test some features of custom RTTI
//
//                       ____InterfaceMock1______________
//                             \                   \
//                              \                   \
//   InterfaceMock2  DerivedFromInterfaceA  DerivedFromInterfaceB
//                 \             /
//                  \           /
//               DerivedFrom2Classes

    
// InterfaceMock1
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in RTTI tests.
/// </summary>
class InterfaceMock1
{
    QE_RTTI_SUPPORT_INTERFACE(InterfaceMock1);
};


// DerivedFromInterfaceA
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in RTTI tests.
/// </summary>
class DerivedFromInterfaceA : public InterfaceMock1
{
    QE_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(DerivedFromInterfaceA, InterfaceMock1);
    
    virtual Kinesis::QuimeraEngine::Common::DataTypes::string_q ToString() const
    {
        return "DerivedFromInterfaceA";
    }
};


// DerivedFromInterfaceB
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in RTTI tests.
/// </summary>
class DerivedFromInterfaceB : public InterfaceMock1
{
	QE_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(DerivedFromInterfaceB, InterfaceMock1);
    
    virtual Kinesis::QuimeraEngine::Common::DataTypes::string_q ToString() const
    {
        return "DerivedFromInterfaceB";
    }
};



// InterfaceMock2
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in RTTI tests.
/// </summary>
class InterfaceMock2
{
    QE_RTTI_SUPPORT_INTERFACE(InterfaceMock2);
};


// DerivedFrom2Classes
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

/// <summary>
/// Class used in RTTI tests.
/// </summary>
class DerivedFrom2Classes : public InterfaceMock2, public DerivedFromInterfaceA
{
    QE_RTTI_SUPPORT_DERIVED_FROM_2_CLASSES(DerivedFrom2Classes, InterfaceMock2, DerivedFromInterfaceA);

    virtual Kinesis::QuimeraEngine::Common::DataTypes::string_q ToString() const
    {
        return "DerivedFrom2Classes";
    }
};



} //namespace Test
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __RTTITESTCLASSES__
