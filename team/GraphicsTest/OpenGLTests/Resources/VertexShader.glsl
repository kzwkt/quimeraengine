#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 inputColor;
layout (location = 2) in vec2 inputTexCoords0;
layout (location = 3) in vec2 inputTexCoords1;
out vec4 colorFromVS;
out vec2 textCoord0;
out vec2 textCoord1;

uniform vec4 uColor;

out gl_PerVertex // In 4.3 core, it's mandatory to redefine this built-in variable in vertex shader
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
	colorFromVS = uColor * inputColor;
	textCoord0 = inputTexCoords0;
	textCoord1 = inputTexCoords1;
}