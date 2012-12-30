// [TERMS&CONDITIONS]

#ifndef __TATMESSAGEFORMAT__
#define __TATMESSAGEFORMAT__

#include "TestExecution/ETATColor.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Describes the format of a message or piece of a message.
/// </summary>
class TATMessageFormat
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Flag for italic text style.
    /// </summary>
    static const unsigned int TEXT_STYLE_ITALIC;

    /// <summary>
    /// Flag for bold text style.
    /// </summary>
    static const unsigned int TEXT_STYLE_BOLD;

    /// <summary>
    /// Flag for underlined text style.
    /// </summary>
    static const unsigned int TEXT_STYLE_UNDERLINE;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATMessageFormat();

    /// <summary>
    /// Constructor that expects a color.
    /// </summary>
    /// <param name="eColor">The color of the text.</param>
    TATMessageFormat(const ETATColor& eColor);
    
    /// <summary>
    /// Constructor that expects a color and a style.
    /// </summary>
    /// <param name="eColor">The color of the text.</param>
    /// <param name="uTextStyle">The style of the text.</param>
    TATMessageFormat(const ETATColor& eColor, const unsigned int uTextStyle);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATMessageFormat();


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Sets the color of the text.
    /// </summary>
    /// <param name="eColor">A color value.</param>
    void SetColor(const ETATColor& eColor);

    /// <summary>
    /// Gets the color of the text.
    /// </summary>
    /// <returns>
    /// A color value.
    /// </returns>
    ETATColor GetColor() const;

    /// <summary>
    /// Sets the style of the text.
    /// </summary>
    /// <param name="uTextStyle">A bit mask, combining the text style flags.</param>
    void SetTextStyle(const unsigned int& uTextStyle);
    
    /// <summary>
    /// Gets the style of the text.
    /// </summary>
    /// <returns>
    /// A bit mask, combining the text style flags.
    /// </returns>
    unsigned int GetTextStyle() const;


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// The color of the text.
    /// </summary>
    ETATColor m_eColor;

    /// <summary>
    /// The text replacements.
    /// </summary>
    std::map<wxString, wxString> m_replacements;

    /// <summary>
    /// The style of the text.
    /// </summary>
    unsigned int m_uTextStyle;

};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATMESSAGEFORMAT__
