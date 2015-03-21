#version 430 core

#pragma debug(on)
#pragma optimize(off)

layout(row_major) uniform;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 inputTexCoords0;
layout (location = 3) in vec2 inputTexCoords1;
out vec4 colorFromVS;
out vec3 outNormal;
out vec2 textCoord0;
out vec2 textCoord1;
out vec3 positionSampled;
out vec3 vLight;

uniform vec4 uColor;
uniform mat4 transformationMatrix;

out gl_PerVertex // In 4.3 core, it's mandatory to redefine this built-in variable in vertex shader
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = position * transformationMatrix;
	outNormal = (vec4(normal, 0.0f) * transformationMatrix).xyz;
	colorFromVS = uColor;
	textCoord0 = inputTexCoords0;
	textCoord1 = inputTexCoords1;
	positionSampled = (position * transformationMatrix).xyz;

	vLight = (vec4(0, 200.0f, -250, 1) * transformationMatrix).xyz;
}