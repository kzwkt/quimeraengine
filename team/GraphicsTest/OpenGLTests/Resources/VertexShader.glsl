#version 430 core

#pragma debug(on)
#pragma optimize(off)

layout(row_major) uniform;

const uint MAX_TEXTURE_LAYERS = 8;

struct InputVertexData
{
	vec4 Position;
	vec3 Normal;
	vec2 TexCoords[MAX_TEXTURE_LAYERS];
};

struct QMaterial
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
};

struct QVisualAspect
{
	QMaterial Material;
};

struct InputOmniLightData
{
	vec4 Position;
};

struct InputDirectionalLightData
{
	vec4 Position;
};

in InputVertexData Input;

uniform Submesh
{
	QVisualAspect Aspect;
};

// Entity level data (not 
uniform Entity
{
	mat4x4 TransformationMatrix;
};

// Scene level data (not contained in an entity)
uniform Scene
{
	InputOmniLightData[32] OmniLights;
	uint OmniLightCount;

	InputDirectionalLightData[32] DirectionalLights;
	uint DirectionalLightCount;

	mat4x4 ViewMatrix;
	mat4x4 ProjectionMatrix;
};

// Configuration settings of the application
uniform Application
{
	vec2 MouseCoords;
	uint FrameTimeDelta;
};

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
    gl_Position = Input.Position * transformationMatrix;
	outNormal = (vec4(Input.Normal, 0.0f) * transformationMatrix).xyz;
	colorFromVS = uColor;
	textCoord0 = Input.TexCoords[0];
	textCoord1 = Input.TexCoords[1];
	positionSampled = (Input.Position * transformationMatrix).xyz;

	vLight = (vec4(0, 200.0f, -250, 1) * transformationMatrix).xyz;
}
