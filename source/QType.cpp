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
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QType* QType::TYPE_INSTANCE_U8 = new QType("u8_q");

const QType* QType::TYPE_INSTANCE_I8 = new QType("i8_q");

const QType* QType::TYPE_INSTANCE_U16 = new QType("u16_q");

const QType* QType::TYPE_INSTANCE_I16 = new QType("i16_q");

const QType* QType::TYPE_INSTANCE_U32 = new QType("u32_q");

const QType* QType::TYPE_INSTANCE_I32 = new QType("i32_q");

const QType* QType::TYPE_INSTANCE_U64 = new QType("u64_q");

const QType* QType::TYPE_INSTANCE_I64 = new QType("i64_q");

const QType* QType::TYPE_INSTANCE_F32 = new QType("f32_q");

const QType* QType::TYPE_INSTANCE_F64 = new QType("f64_q");

const QType* QType::TYPE_INSTANCE_VF32 = new QType("vf32_q");


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QType::QType(const string_q &strName) : m_strName(strName)
{
}
	

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
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

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const string_q& QType::GetName() const
{
    return m_strName;
}

} //namespace DataTypes
} //namespace Common
} //namespace QuimeraEngine
} //namespace Kinesis
