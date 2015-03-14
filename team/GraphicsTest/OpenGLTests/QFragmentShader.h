
#ifndef __QFRAGMENTSHADER__
#define __QFRAGMENTSHADER__

class QFragmentShader
{
public:

    QFragmentShader(GLuint shaderProgramID) : m_shaderProgramID(shaderProgramID)
    {
    }
        
    GLuint GetProgramID()
    {
        return m_shaderProgramID;
    }

protected:

    GLuint m_shaderProgramID;
};

#endif // __QFRAGMENTSHADER__