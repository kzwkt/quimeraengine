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

#include "QBaseDualQuaternion.h"

#include "SQFloat.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;

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

QBaseDualQuaternion::QBaseDualQuaternion() : r(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0)),
                                d(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0))
{
}

QBaseDualQuaternion::QBaseDualQuaternion(const QBaseDualQuaternion &dualQuat)
{
	this->r.x = dualQuat.r.x;
	this->d.x = dualQuat.d.x;
	this->r.y = dualQuat.r.y;
	this->d.y = dualQuat.d.y;
	this->r.z = dualQuat.r.z;
	this->d.z = dualQuat.d.z;
	this->r.w = dualQuat.r.w;
    this->d.w = dualQuat.d.w;
}

QBaseDualQuaternion::QBaseDualQuaternion(const QBaseQuaternion &qReal, const QBaseQuaternion &qDual) : r(qReal), d(qDual)
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

bool QBaseDualQuaternion::operator==(const QBaseDualQuaternion &dualQuat) const
{
    return this->r == dualQuat.r && this->d == dualQuat.d;
}

bool QBaseDualQuaternion::operator!=(const QBaseDualQuaternion &dualQuat) const
{
    return !(*this == dualQuat);
}



} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
