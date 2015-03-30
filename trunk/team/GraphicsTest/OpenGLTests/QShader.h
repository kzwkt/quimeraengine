
#ifndef __QSHADER__
#define __QSHADER__

#include <GL/glew.h>

#include "QuimeraEngineIncludesAndUsings.h"

class QShader
{

public:

    enum EQShaderType
    {
        E_VertexShader,
        E_FragmentShader,
        E_GeometryShader,
        E_TesselationControlShader, // Hull shader
        E_TesselationEvaluationShader, // Domain shader
        E_ComputeShader
    };

    QShader(GLuint shaderProgramID) : m_shaderProgramID(shaderProgramID)
    {
        this->_GetShaderInterfaceInfo();
    }

    GLuint GetExternalId()
    {
        return m_shaderProgramID;
    }

protected:

    void _GetShaderInterfaceInfo()
    {
        GLint numActiveAttribs = 0;
        GLint numActiveUniforms = 0;
        glGetProgramInterfaceiv(m_shaderProgramID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
        glGetProgramInterfaceiv(m_shaderProgramID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms);


        std::vector<GLchar> nameData(256);
        std::vector<GLenum> properties;
        properties.push_back(GL_NAME_LENGTH);
        properties.push_back(GL_TYPE);
        properties.push_back(GL_ARRAY_SIZE);
        std::vector<GLint> values(properties.size());
        for (int attrib = 0; attrib < numActiveAttribs; ++attrib)
        {
            glGetProgramResourceiv(m_shaderProgramID, GL_PROGRAM_INPUT, attrib, properties.size(),
                &properties[0], values.size(), NULL, &values[0]);

            nameData.resize(properties[0]); //The length of the name.
            glGetProgramResourceName(m_shaderProgramID, GL_PROGRAM_INPUT, attrib, nameData.size(), NULL, &nameData[0]);
            std::string name((char*)&nameData[0], nameData.size() - 1);

            QE_LOG(string_q(name.c_str()) + "\n");
        }
    }

    QDictionary<const char*, u32_q> m_inputs;
    QDictionary<const char*, u32_q> m_buffers;

    GLuint m_shaderProgramID;
};

#endif // __QSHADER__