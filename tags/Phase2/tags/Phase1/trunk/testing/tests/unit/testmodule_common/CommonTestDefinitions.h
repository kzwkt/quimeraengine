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

#ifndef __COMMONTESTDEFINITIONS__
#define __COMMONTESTDEFINITIONS__

// --------------------------------------------------------------------------------------------------------
// QStringUnicode::Normalization test switch: This switch enables or disables the tests of the Normalize
// method of the class QStringUnicode, which takes a lot of time.
// --------------------------------------------------------------------------------------------------------
#define QE_TEST_CONFIG_QSTRINGUNICODE_NORMALIZE_TEST_ENABLED 0x0
#define QE_TEST_CONFIG_QSTRINGUNICODE_NORMALIZE_TEST_DISABLED 0x1

#define QE_TEST_CONFIG_QSTRINGUNICODE_NORMALIZE_TEST QE_TEST_CONFIG_QSTRINGUNICODE_NORMALIZE_TEST_DISABLED

// --------------------------------------------------------------------------------------------------------
// QStringUnicode::CompareTo test switch: This switch enables or disables the tests of the CompareTo
// method of the class QStringUnicode, which takes a lot of time.
// --------------------------------------------------------------------------------------------------------
#define QE_TEST_CONFIG_QSTRINGUNICODE_COMPARE_TEST_ENABLED 0x0
#define QE_TEST_CONFIG_QSTRINGUNICODE_COMPARE_TEST_DISABLED 0x1

#define QE_TEST_CONFIG_QSTRINGUNICODE_COMPARE_TEST QE_TEST_CONFIG_QSTRINGUNICODE_COMPARE_TEST_ENABLED

#endif // __COMMONTESTDEFINITIONS__
