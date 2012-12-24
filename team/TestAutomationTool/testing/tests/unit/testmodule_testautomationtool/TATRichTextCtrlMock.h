// [TERMS&CONDITIONS]

#ifndef __TATRICHTEXTCTRLMOCK__
#define __TATRICHTEXTCTRLMOCK__

#include <wx/richtext/richtextctrl.h>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{
namespace Test
{

/// <summary>
/// A mock derived from wxRichTextCtrl for testing purposes.
/// </summary>
class TATRichTextCtrlMock : public wxRichTextCtrl
{
public:

    virtual void WriteText(const wxString& text)
    {
        m_strText += text;
    }

    virtual wxString GetValue() const
    {
       return m_strText;
    }

protected:

    wxString m_strText;
};

} //namespace Test
} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATRICHTEXTCTRLMOCK__