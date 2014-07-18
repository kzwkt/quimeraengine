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

#include "QBaseQuadrilateral.h"

#include "SQFloat.h"
#include "SQVF32.h"

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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QBaseQuadrilateral::QBaseQuadrilateral() : A(SQFloat::_0), B(SQFloat::_0), C(SQFloat::_0), D(SQFloat::_0)
{
}

QBaseQuadrilateral::QBaseQuadrilateral(const QBaseQuadrilateral &quad) : A(quad.A), B(quad.B), C(quad.C), D(quad.D)
{
}

QBaseQuadrilateral::QBaseQuadrilateral(const QVector2 &vA, const QVector2 &vB,
                            const QVector2 &vC, const QVector2 &vD) :
                            A(vA), B(vB), C(vC), D(vD)
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

bool QBaseQuadrilateral::operator==(const QBaseQuadrilateral &quad) const
{
    return ( this->A == quad.A && this->B == quad.B && this->C == quad.C && this->D == quad.D );
}

bool QBaseQuadrilateral::operator!=(const QBaseQuadrilateral &quad) const
{
    return !(*this == quad);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
