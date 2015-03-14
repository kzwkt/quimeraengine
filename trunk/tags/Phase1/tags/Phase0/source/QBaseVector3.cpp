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

#include "QBaseVector3.h"

#include "SQFloat.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QBaseVector3::QBaseVector3() : x(SQFloat::_0), y(SQFloat::_0), z(SQFloat::_0)
{
}

QBaseVector3::QBaseVector3(const QBaseVector3 &vVector)
{
	this->x = vVector.x;
	this->y = vVector.y;
	this->z = vVector.z;
}

QBaseVector3::QBaseVector3(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ) :
                                x(fValueX), y(fValueY), z(fValueZ)
{
}

QBaseVector3::QBaseVector3(const float_q &fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll)
{
}

QBaseVector3::QBaseVector3(const float_q* arValues)
{
	// Null pointer checkout
	QE_ASSERT(arValues != null_q)

	// Assignments
	this->x = arValues[0];
	this->y = arValues[1];
	this->z = arValues[2];
}

QBaseVector3::QBaseVector3(const vf32_q value)
{
    using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;

	float_q fAux;

	SQVF32::Unpack(value, this->x, this->y, this->z, fAux);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

bool QBaseVector3::operator==(const QBaseVector3 &vVector) const
{
    return ( SQFloat::AreEqual(vVector.x, this->x) && SQFloat::AreEqual(vVector.y, this->y) && SQFloat::AreEqual(vVector.z, this->z) );
}

bool QBaseVector3::operator!=(const QBaseVector3 &vVector) const
{
    return !(*this == vVector);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
