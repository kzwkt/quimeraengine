#version 430 core

layout(row_major) uniform;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 inputTexCoords0;
layout (location = 2) in vec2 inputTexCoords1;
out vec4 colorFromVS;
out vec2 textCoord0;
out vec2 textCoord1;

uniform vec4 uColor;
uniform mat4 transformationMatrix;

out gl_PerVertex // In 4.3 core, it's mandatory to redefine this built-in variable in vertex shader
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = position * transformationMatrix;
	colorFromVS = uColor;
	textCoord0 = inputTexCoords0;
	textCoord1 = inputTexCoords1;
}