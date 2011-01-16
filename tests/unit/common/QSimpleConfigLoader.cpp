// [TERMS&CONDITIONS]
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
