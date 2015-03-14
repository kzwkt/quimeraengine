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

#ifndef __QUIMERAENGINEFIXTURES__
#define __QUIMERAENGINEFIXTURES__

#define QTEST_SUITE_FIXTURE( fixture_class_name, suite_name )                   \
class fixture_class_name                                                        \
{                                                                               \
public:                                                                         \
    fixture_class_name()                                                        \
    {                                                                           \
        BOOST_TEST_MESSAGE(std::string("Starting Test Fixture ") + suite_name); \
    }                                                                           \
                                                                                \
    ~fixture_class_name()                                                       \
    {                                                                           \
        BOOST_TEST_MESSAGE(std::string("Ending Test Fixture ") + suite_name);   \
    }                                                                           \
};

#endif // __QUIMERAENGINEFIXTURES__
