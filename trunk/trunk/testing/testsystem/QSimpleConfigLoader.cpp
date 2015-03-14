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
#include <fstream>

#include "QSimpleConfigLoader.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Test
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QSimpleConfigLoader::QSimpleConfigLoader()
{
}

QSimpleConfigLoader::QSimpleConfigLoader(const std::string &strPath)
{
    this->SetFilePath(strPath);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QSimpleConfigLoader::~QSimpleConfigLoader()
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

const std::string& QSimpleConfigLoader::operator[](const int &index) const
{
    return _arConfigEntries[index];
}

bool QSimpleConfigLoader::LoadEntries()
{
    if(!_strPath.empty())
    {
        try
        {
            // Opens the file
            std::ifstream inputFile(_strPath.c_str());

            if(inputFile.is_open())
            {
                // For each text line, until reaches the end of the file
                std::string strLine;
                bool bEOF = false;

                while(!bEOF)
                {
                    bEOF = (inputFile >> strLine).eof();
                    _arConfigEntries.push_back(strLine);
                }

                // All entries were read, if any
                return true;
            }
        }
        catch(std::exception ex)
        {
            // Silences the exception, it doesn't matters
        }
    }

    // If there was any problem, the execution path ends here
    return false;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

std::string QSimpleConfigLoader::GetFilePath() const
{
    return this->_strPath;
}

void QSimpleConfigLoader::SetFilePath(const std::string &strPath)
{
    this->_strPath = strPath;
}

} //namespace Test
} //namespace QuimeraEngine
} //namespace Kinesis
