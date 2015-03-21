#version 430 core

#pragma debug(on)
#pragma optimize(off)

layout(row_major) uniform;

in vec3 positionSampled;
in vec4 colorFromVS;
in vec3 normal;
in vec2 textCoord0;
in vec2 textCoord1;
out vec4 color;

uniform sampler2D sampler1;
uniform sampler2D sampler2;

in vec3 vLight;

void main()
{
	float fLightMaxDist = 30.0f;
	vec3 vLightVector = vLight - positionSampled;

	vec3 viewToPosition = normalize(-positionSampled);
	vec3 lightToPosition = normalize(-vLightVector);
	vec3 reflectedLight = reflect(lightToPosition, normal);

	float fSpecularPower = pow(max(dot(viewToPosition, reflectedLight), 0.0), 4);

	vec4 outputColor = (vec4(0.3, 0.3, 0.3, 1.0) + fSpecularPower * 0.3f + max(dot(normalize(vLightVector), normalize(normal)), 0) * max(fLightMaxDist / length(vLightVector), 1.0f)) * texture(sampler1, textCoord0);// colorFromVS * mix(texture(sampler1, textCoord1), texture(sampler2, textCoord0 + vec2(0.2, 0.2)), 1.0 - texture(sampler1, textCoord1).a);;
    color = vec4(clamp(outputColor.r, 0.0f, 1.0f), clamp(outputColor.g, 0.0f, 1.0f), clamp(outputColor.b, 0.0f, 1.0f), clamp(outputColor.a, 0.0f, 1.0f));
}