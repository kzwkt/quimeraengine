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

#include "EQTreeTraversalOrder.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Containers
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

EQTreeTraversalOrder::TNameValuePair EQTreeTraversalOrder::sm_arValueName[] =
    {
        std::pair<string_q, EQTreeTraversalOrder::EnumType>(QE_L("DepthFirstInOrder"),   EQTreeTraversalOrder::E_DepthFirstInOrder),
        std::pair<string_q, EQTreeTraversalOrder::EnumType>(QE_L("DepthFirstPreOrder"),  EQTreeTraversalOrder::E_DepthFirstPreOrder),
        std::pair<string_q, EQTreeTraversalOrder::EnumType>(QE_L("DepthFirstPostOrder"), EQTreeTraversalOrder::E_DepthFirstPostOrder),
        std::pair<string_q, EQTreeTraversalOrder::EnumType>(QE_L("BreadthFirst"),        EQTreeTraversalOrder::E_BreadthFirst),
    };

EQTreeTraversalOrder::TNameValueMap EQTreeTraversalOrder::sm_mapValueName(
        EQTreeTraversalOrder::sm_arValueName ,
        &EQTreeTraversalOrder::sm_arValueName[0] + sizeof(EQTreeTraversalOrder::sm_arValueName) / sizeof(EQTreeTraversalOrder::sm_arValueName[0])
    );

} //namespace Containers
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
