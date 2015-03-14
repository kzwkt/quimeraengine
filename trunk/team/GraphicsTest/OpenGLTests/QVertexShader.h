
#ifndef __QVERTEXSHADER__
#define __QVERTEXSHADER__

class QVertexShader
{
public:

    QVertexShader(GLuint shaderProgramID) : m_shaderProgramID(shaderProgramID)
    {
    }

    GLuint GetProgramID()
    {
        return m_shaderProgramID;
    }

protected:

    GLuint m_shaderProgramID;
};

#endif // __QVERTEXSHADER__