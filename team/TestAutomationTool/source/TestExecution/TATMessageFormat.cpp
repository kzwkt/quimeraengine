// [TERMS&CONDITIONS]

#include "TestExecution/TATMessageFormat.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const unsigned int TATMessageFormat::TEXT_STYLE_ITALIC = 1;

const unsigned int TATMessageFormat::TEXT_STYLE_BOLD = 2;

const unsigned int TATMessageFormat::TEXT_STYLE_UNDERLINE = 4;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATMessageFormat::TATMessageFormat() : m_eColor(ETATColor::E_Black),
                                       m_uTextStyle(0)
{
}
	
TATMessageFormat::TATMessageFormat(const ETATColor& eColor) : m_eColor(eColor),
                                                              m_uTextStyle(0)
{
}

TATMessageFormat::TATMessageFormat(const ETATColor& eColor, const unsigned int uTextStyle) : m_eColor(eColor),
                                                                                             m_uTextStyle(uTextStyle)
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATMessageFormat::~TATMessageFormat()
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATMessageFormat::SetColor(const ETATColor& eColor)
{
    m_eColor = eColor;
}

ETATColor TATMessageFormat::GetColor() const
{
    return m_eColor;
}

void TATMessageFormat::SetTextStyle(const unsigned int& uTextStyle)
{
    m_uTextStyle = uTextStyle;
}

unsigned int TATMessageFormat::GetTextStyle() const
{
    return m_uTextStyle;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
