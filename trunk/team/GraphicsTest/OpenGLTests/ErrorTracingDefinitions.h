
#ifndef __ERRORTRACINGDEFINITIONS__
#define __ERRORTRACINGDEFINITIONS__

#define QE_ASSERT_WINDOWS_ERROR(strErrorMessage) \
    DWORD errorMessageID = ::GetLastError(); \
    if(errorMessageID != 0) \
    { \
        LPTSTR szMessageBuffer = null_q; \
        size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, \
                                    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szMessageBuffer, 0, NULL); \
                                     \
        QE_ASSERT_ERROR(false, string_q(strErrorMessage) + " Error: 0x" + string_q::FromIntegerToHexadecimal(scast_q(errorMessageID, u32_q)) + ". " + string_q(szMessageBuffer)); \
        \
        ::LocalFree(szMessageBuffer); \
    }


#define QE_ASSERT_OPENGL_ERROR(strErrorMessage, eErrorCode) \
    if(errorMessageID != 0) \
    { \
        const GLubyte* szMessage = gluErrorString(eErrorCode); \
                                     \
        QE_ASSERT_ERROR(false, string_q(strErrorMessage) + " Error: 0x" + string_q::FromIntegerToHexadecimal(scast_q(eErrorCode, u32_q)) + ". " + string_q(rcast_q(szMessge, const i8_q*)); \
    }

#define QE_TRACE_WINDOWS_ERROR(strErrorMessage) \
    DWORD errorMessageID = ::GetLastError(); \
    if(errorMessageID != 0) \
    { \
        LPTSTR szMessageBuffer = null_q; \
        size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, \
                                    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szMessageBuffer, 0, NULL); \
                                     \
        QE_LOG(string_q("LOG: ") + string_q(strErrorMessage) + " Error: 0x" + string_q::FromIntegerToHexadecimal(scast_q(errorMessageID, u32_q)) + ". " + string_q(szMessageBuffer)); \
        \
        ::LocalFree(szMessageBuffer); \
    }


#define QE_TRACE_OPENGL_ERROR(strErrorMessage, eErrorCode) \
    if(errorMessageID != 0) \
    { \
        const GLubyte* szMessage = gluErrorString(eErrorCode); \
                                     \
        QE_LOG(string_q("LOG: ") + string_q(strErrorMessage) + " Error: 0x" + string_q::FromIntegerToHexadecimal(scast_q(eErrorCode, u32_q)) + ". " + string_q(rcast_q(szMessge, const i8_q*)); \
    }

#endif // __ERRORTRACINGDEFINITIONS__