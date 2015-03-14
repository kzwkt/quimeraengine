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

#ifndef __TESTINGHELPERDEFINITIONS__
#define __TESTINGHELPERDEFINITIONS__

// --------------------------------------------------------------------------------------------------------
// QUNITTEST_MODULE_CONFIG: Use this macro to define a new unit test module with no additional logic. In case
// some logic has to be implemented in the constructor or the destructor, a new class has to be defined
// manually, inheriting from QUnitTestModuleBase in the same way this macro does.
// Note: Remember to include the files in which the classes used here are defined before using this macro.
// --------------------------------------------------------------------------------------------------------
#define QUNITTEST_MODULE_CONFIG( ModuleName )   using Kinesis::QuimeraEngine::Test::QUnitTestModuleBase;                      \
                                                                                                                              \
                                                class TestModuleConfiguration##ModuleName : public QUnitTestModuleBase        \
                                                {                                                                             \
                                                public:                                                                       \
                                                    TestModuleConfiguration##ModuleName() : QUnitTestModuleBase(#ModuleName)  \
                                                    {                                                                         \
                                                    }                                                                         \
                                                                                                                              \
                                                    virtual ~TestModuleConfiguration##ModuleName()                            \
                                                    {                                                                         \
                                                    }                                                                         \
                                                };                                                                            \
                                                                                                                              \
                                                BOOST_GLOBAL_FIXTURE( TestModuleConfiguration##ModuleName );

// --------------------------------------------------------------------------------------------------------
// QPERFORMANCETEST_MODULE_CONFIG: Use this macro to define a new performance test module with no additional logic. 
// In case some logic has to be implemented in the constructor or the destructor, a new class has to be defined
// manually, inheriting from QPerformanceTestModuleBase in the same way this macro does.
// Note: Remember to include the files in which the classes used here are defined before using this macro.
// --------------------------------------------------------------------------------------------------------
#define QPERFORMANCETEST_MODULE_CONFIG( ModuleName )   using Kinesis::QuimeraEngine::Test::QPerformanceTestModuleBase;                      \
                                                                                                                                            \
                                                       class TestModuleConfiguration##ModuleName : public QPerformanceTestModuleBase        \
                                                       {                                                                                    \
                                                       public:                                                                              \
                                                           TestModuleConfiguration##ModuleName() : QPerformanceTestModuleBase(#ModuleName)  \
                                                           {                                                                                \
                                                           }                                                                                \
                                                                                                                                            \
                                                           virtual ~TestModuleConfiguration##ModuleName()                                   \
                                                           {                                                                                \
                                                           }                                                                                \
                                                       };                                                                                   \
                                                                                                                                            \
                                                       BOOST_GLOBAL_FIXTURE( TestModuleConfiguration##ModuleName );

#endif // __TESTINGHELPERDEFINITIONS__