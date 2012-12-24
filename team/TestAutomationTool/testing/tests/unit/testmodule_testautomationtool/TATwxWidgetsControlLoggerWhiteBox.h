// [TERMS&CONDITIONS]

#ifndef __TATWXWIDGETSCONTROLLOGGERWHITEBOX__
#define __TATWXWIDGETSCONTROLLOGGERWHITEBOX__

#include "TestExecution/TATwxWidgetsControlLogger.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// Class intented to be used to expose protected methods of TATwxWidgetsControlLogger for testing purposes.
/// </summary>
class TATwxWidgetsControlLoggerWhiteBox : public TATwxWidgetsControlLogger
{
public:

    TATwxWidgetsControlLoggerWhiteBox(wxRichTextCtrl* pControl, const bool& bAutoFlush=true) : TATwxWidgetsControlLogger(pControl, bAutoFlush)
    {
    }

    using TATwxWidgetsControlLogger::WriteMessage;
    using TATwxWidgetsControlLogger::WriteMessagePart;
    using TATwxWidgetsControlLogger::TranslateColor;
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATWXWIDGETSCONTROLLOGGERWHITEBOX__
