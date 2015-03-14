
#ifndef __QSHADERCOMPOSITOR__
#define __QSHADERCOMPOSITOR__

#include "GL/glew.h"
#include "GL/wglew.h"
#include "QuimeraEngineIncludesAndUsings.h"
#include "QVertexShader.h"
#include "QFragmentShader.h"

class QShaderCompositor
{
public:

    virtual QVertexShader* CompileAndLinkVertexShader(const QPath &vertexShaderPath)
    {
        QVertexShader* pResultantVertexShader = null_q;

        // Reads the vertex shader from text file
        string_q strFileContent;
        EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
        QFileStream fs(vertexShaderPath, EQFileOpenMode::E_Open, 500, eErrorInfo);
        QTextStreamReader<QFileStream> ts(fs, EQTextEncoding::E_ASCII);
        ts.ReadToEnd(strFileContent);
        fs.Close();
    
        // Adapts the content
        QArrayResult<i8_q> arFileContent = strFileContent.ToBytes(EQTextEncoding::E_ASCII);
        const char* szFileContent = arFileContent.Get();

        // Compiles the vertex shader
        QE_LOG("LOG: Compiling vertex shader...\n");
        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &szFileContent, null_q);
        glCompileShader(vertexShaderID);

        // Checks result
        GLint nSucceed = 0;
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &nSucceed);

        if(!nSucceed)
        {
            GLsizei nActualLength = 0;
            GLchar szErrorMessage[512];
            glGetShaderInfoLog(vertexShaderID, 512, &nActualLength, szErrorMessage);

            QE_ASSERT_ERROR(false, szErrorMessage);
        }

        QE_LOG("LOG: Vertex shader compiled successfully.\n");

        pResultantVertexShader = new QVertexShader(QShaderCompositor::_LinkShader(vertexShaderID));

        glDetachShader(pResultantVertexShader->GetProgramID(), vertexShaderID);
        glDeleteShader(vertexShaderID);

        return pResultantVertexShader;
    }
        
    virtual QFragmentShader* CompileAndLinkFragmentShader(const QPath &vertexShaderPath)
    {
        QFragmentShader* pResultantFragmentShader = null_q;

        // Reads the fragment shader from text file
        string_q strFileContent;
        EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
        QFileStream fs(vertexShaderPath, EQFileOpenMode::E_Open, 500, eErrorInfo);
        QTextStreamReader<QFileStream> ts(fs, EQTextEncoding::E_ASCII);
        strFileContent = string_q::GetEmpty();
        ts.ReadToEnd(strFileContent);
        fs.Close();

        // Adapts the content
        QArrayResult<i8_q> arFileContent = strFileContent.ToBytes(EQTextEncoding::E_ASCII);
        const char* szFileContent = arFileContent.Get();

        // Compiles the fragment shader
        QE_LOG("LOG: Compiling fragment shader...\n");
        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, &szFileContent, null_q);
        glCompileShader(fragmentShaderID);

        // Checks result
        GLint nSucceed = 0;
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &nSucceed);

        if(!nSucceed)
        {
            GLsizei nActualLength = 0;
            GLchar szErrorMessage[512];
            glGetShaderInfoLog(fragmentShaderID, 512, &nActualLength, szErrorMessage);

            QE_ASSERT_ERROR(false, szErrorMessage);
        }

        QE_LOG("LOG: Fragment shader compiled successfully.\n");

        pResultantFragmentShader = new QFragmentShader(QShaderCompositor::_LinkShader(fragmentShaderID));

        glDetachShader(pResultantFragmentShader->GetProgramID(), fragmentShaderID);
        glDeleteShader(fragmentShaderID);

        return pResultantFragmentShader;
    }
    
protected:

    static GLuint _LinkShader(GLuint shaderID)
    {
        GLuint shaderProgramID = glCreateProgram();

        // Links the program
        QE_LOG("LOG: Linking shader program...\n");
        
        glProgramParameteri(shaderProgramID, GL_PROGRAM_SEPARABLE, GL_TRUE);
        glAttachShader(shaderProgramID, shaderID);
        glLinkProgram(shaderProgramID);

        // Checks result
        GLint nSucceed = 0;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &nSucceed);

        if(!nSucceed)
        {
            GLsizei nActualLength = 0;
            GLchar szErrorMessage[512];
            glGetProgramInfoLog(shaderProgramID, 512, &nActualLength, szErrorMessage);

            QE_ASSERT_ERROR(false, szErrorMessage);
        }

        QE_LOG("LOG: Shader program linked successfully.\n");

        return shaderProgramID;
    }
};

#endif // __QSHADERCOMPOSITOR__