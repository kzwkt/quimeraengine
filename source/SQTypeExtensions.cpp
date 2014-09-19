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

#include "SQTypeExtensions.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Common
{
namespace DataTypes
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
    
bool SQTypeExtensions::IsObject(const void* pObject)
{
    return false;
}

bool SQTypeExtensions::IsObject(const Kinesis::QuimeraEngine::Core::QObject* pObject)
{
    return true;
}

template<>
const QType* SQTypeExtensions::FindType(const bool &object)
{
    return QType::FindType<bool>();
}

template<>
const QType* SQTypeExtensions::FindType(const u8_q &object)
{
    return QType::FindType<u8_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const u16_q &object)
{
    return QType::FindType<u16_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const u32_q &object)
{
    return QType::FindType<u32_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const u64_q &object)
{
    return QType::FindType<u64_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const i8_q &object)
{
    return QType::FindType<i8_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const i16_q &object)
{
    return QType::FindType<i16_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const i32_q &object)
{
    return QType::FindType<i32_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const i64_q &object)
{
    return QType::FindType<i64_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const f32_q &object)
{
    return QType::FindType<f32_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const f64_q &object)
{
    return QType::FindType<f64_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const vf32_q &object)
{
    return QType::FindType<vf32_q>();
}

template<>
const QType* SQTypeExtensions::FindType(const string_q &object)
{
    return QType::FindType<string_q>();
}

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
