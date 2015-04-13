
#ifndef __QSHADERCOMPOSITOR__
#define __QSHADERCOMPOSITOR__

#include "GL/glew.h"
#include "GL/wglew.h"
#include "QuimeraEngineIncludesAndUsings.h"
#include "ErrorTracingDefinitions.h"
#include "QShader.h"
#include "QShader.h"

class QShaderCompositor
{
public:

    virtual QShader* CompileAndLinkShader(const QPath &shaderPath, const QShader::EQShaderType eShaderType, const QArrayDynamic<const char*>* arIncludes, const QArrayDynamic< QKeyValuePair<const char*, const char*> >* arPreprocessorDefinitions)
    {
        // [TODO]: Implement includes and preprocessor definitions

        QShader* pResultantShader = null_q;

        // Reads the shader from text file
        string_q strFileContent;
        EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
        QFileStream fs(shaderPath, EQFileOpenMode::E_Open, SQFile::GetFileInfo(shaderPath, eErrorInfo).GetSize(), eErrorInfo);
        QTextStreamReader<QFileStream> ts(fs, EQTextEncoding::E_ASCII);
        ts.ReadToEnd(strFileContent);
        fs.Close();
    
        // Adapts the content
        QArrayResult<i8_q> arFileContent = strFileContent.ToBytes(EQTextEncoding::E_ASCII);
        const char* szFileContent = arFileContent.Get();

        // Compiles the vertex shader
        QE_LOG("LOG: Compiling shader...\n");
        GLuint shaderID = glCreateShader(QShaderCompositor::_GetEquivalentShaderTypeOpenGLValue(eShaderType));
        glShaderSource(shaderID, 1, &szFileContent, null_q);
        glCompileShader(shaderID);

        // Checks result
        GLint nSucceed = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &nSucceed);

        if(!nSucceed)
        {
            GLsizei nActualLength = 0;
            GLchar szErrorMessage[512];
            glGetShaderInfoLog(shaderID, 512, &nActualLength, szErrorMessage);

            QE_ASSERT_ERROR(false, szErrorMessage);
        }

        QE_LOG("LOG: Shader compiled successfully.\n");

        pResultantShader = new QShader(QShaderCompositor::_LinkShader(shaderID));

        glDetachShader(pResultantShader->GetExternalId(), shaderID);
        glDeleteShader(shaderID);

        return pResultantShader;
    }
    
protected:

    static GLuint _LinkShader(GLuint shaderID)
    {
        GLuint shaderProgramID = glCreateProgram();

        // Links the program
        QE_LOG("LOG: Linking shader program...\n");
        
        glProgramParameteri(shaderProgramID, GL_PROGRAM_SEPARABLE, GL_TRUE);

        QE_ASSERT_OPENGL_ERROR("An error occurred when setting a property of the program (glProgramParameteri).");

        glAttachShader(shaderProgramID, shaderID);
        glLinkProgram(shaderProgramID);

        QE_ASSERT_OPENGL_ERROR("An error occurred when linking the program (glLinkProgram).");

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

    static GLenum _GetEquivalentShaderTypeOpenGLValue(const QShader::EQShaderType eShaderType)
    {
        static const GLenum EQUIVALENCIES[] = { 
                                                GL_VERTEX_SHADER,
                                                GL_FRAGMENT_SHADER,
                                                GL_GEOMETRY_SHADER,
                                                GL_TESS_CONTROL_SHADER, 
                                                GL_TESS_EVALUATION_SHADER, 
                                                GL_COMPUTE_SHADER
                                              };

        return EQUIVALENCIES[eShaderType];
    }
};

#endif // __QSHADERCOMPOSITOR__