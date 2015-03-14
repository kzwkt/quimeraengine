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

#include "QType.h"
#include "Assertions.h"


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
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QType* QType::TYPE_INSTANCE_BOOL = new QType("bool");

const QType* QType::TYPE_INSTANCE_U8 = new QType("u8");

const QType* QType::TYPE_INSTANCE_I8 = new QType("i8");

const QType* QType::TYPE_INSTANCE_U16 = new QType("u16");

const QType* QType::TYPE_INSTANCE_I16 = new QType("i16");

const QType* QType::TYPE_INSTANCE_U32 = new QType("u32");

const QType* QType::TYPE_INSTANCE_I32 = new QType("i32");

const QType* QType::TYPE_INSTANCE_U64 = new QType("u64");

const QType* QType::TYPE_INSTANCE_I64 = new QType("i64");

const QType* QType::TYPE_INSTANCE_F32 = new QType("f32");

const QType* QType::TYPE_INSTANCE_F64 = new QType("f64");

const QType* QType::TYPE_INSTANCE_VF32 = new QType("vf32");

const QType* QType::TYPE_INSTANCE_STRING = new QType("string");

const QType* QType::TYPE_INSTANCE_VOID = new QType("void");

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QType::QType(const string_q &strName) : m_strName(strName)
{
}
    

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QType::operator==(const QType &type) const
{
    return this == &type;
}

bool QType::operator!=(const QType &type) const
{
    return this != &type;
}

template<>
const QType* QType::FindType<bool>()
{
    return TYPE_INSTANCE_BOOL;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u8_q>()
{
    return TYPE_INSTANCE_U8;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i8_q>()
{
    return TYPE_INSTANCE_I8;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u16_q>()
{
    return TYPE_INSTANCE_U16;
}
    
template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i16_q>()
{
    return TYPE_INSTANCE_I16;
}
    
template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u32_q>()
{
    return TYPE_INSTANCE_U32;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i32_q>()
{
    return TYPE_INSTANCE_I32;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::u64_q>()
{
    return TYPE_INSTANCE_U64;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::i64_q>()
{
    return TYPE_INSTANCE_I64;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::f32_q>()
{
    return TYPE_INSTANCE_F32;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::f64_q>()
{
    return TYPE_INSTANCE_F64;
}
    
template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::vf32_q>()
{
    return TYPE_INSTANCE_VF32;
}

template<>
const QType* QType::FindType<Kinesis::QuimeraEngine::Common::DataTypes::string_q>()
{
    return TYPE_INSTANCE_STRING;
}

template<>
const QType* QType::FindType<void>()
{
    return TYPE_INSTANCE_VOID;
}

template<>
const QType* QType::FindType(const bool &)
{
    return QType::FindType<bool>();
}

template<>
const QType* QType::FindType(const u8_q &)
{
    return QType::FindType<u8_q>();
}

template<>
const QType* QType::FindType(const u16_q &)
{
    return QType::FindType<u16_q>();
}

template<>
const QType* QType::FindType(const u32_q &)
{
    return QType::FindType<u32_q>();
}

template<>
const QType* QType::FindType(const u64_q &)
{
    return QType::FindType<u64_q>();
}

template<>
const QType* QType::FindType(const i8_q &)
{
    return QType::FindType<i8_q>();
}

template<>
const QType* QType::FindType(const i16_q &)
{
    return QType::FindType<i16_q>();
}

template<>
const QType* QType::FindType(const i32_q &)
{
    return QType::FindType<i32_q>();
}

template<>
const QType* QType::FindType(const i64_q &)
{
    return QType::FindType<i64_q>();
}

template<>
const QType* QType::FindType(const f32_q &)
{
    return QType::FindType<f32_q>();
}

template<>
const QType* QType::FindType(const f64_q &)
{
    return QType::FindType<f64_q>();
}

template<>
const QType* QType::FindType(const vf32_q &)
{
    return QType::FindType<vf32_q>();
}

template<>
const QType* QType::FindType(const string_q &)
{
    return QType::FindType<string_q>();
}

template<>
const QType* QType::FindType(void*)
{
    return QType::FindType<void>();
}

template<>
const QType* QType::FindType(const void*)
{
    return QType::FindType<void>();
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const string_q& QType::GetName() const
{
    return m_strName;
}

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
