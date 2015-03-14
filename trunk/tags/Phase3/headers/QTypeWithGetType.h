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

#ifndef __QTYPEWITHGETTYPE__
#define __QTYPEWITHGETTYPE__

#include "SystemDefinitions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace Diagnosis
{

/// <summary>
/// Constructor overload selector used to call a constructor that expects an argument to provide a non-static method called GetTypeObject and 
/// a static method called GetTypeClass, which receive no parameters and return a pointer to a QType instance.<br/>
/// Overload selectors are intended to be instanced in the function call and passed as argument so the compiler calls the desired
/// overload based on the type of the parameters.
/// </summary>
class QE_LAYER_SYSTEM_SYMBOLS QTypeWithGetType
{
};

} //namespace Diagnosis
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTYPEWITHGETTYPE__
