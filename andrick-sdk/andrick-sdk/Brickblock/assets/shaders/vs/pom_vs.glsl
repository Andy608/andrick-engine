#version 330 core

layout (location = 0)	in vec4 aPosition;
layout (location = 1)	in vec4 aTexcoord;
layout (location = 2)	in vec3 aNormal;
layout (location = 3)   in vec3 aTangent;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformMatrix;

out mat4 TangentBasis;
out vec2 TexCoords;

void main()
{
	mat4 modelView =  viewMatrix * transformMatrix;
	vec3 normal = normalize(aNormal);
	vec3 tangent = normalize((projectionMatrix * vec4(aTangent, 0.0)).xyz);
	//vec3 tangent = (projectionMatrix * (transformMatrix * vec4(normal, 0.0))).xyz;
	//vec3 tangent = cross( normal, (projectionMatrix * vec4(0.0f, -1.0f, 0.0f, 0.0f)).xyz );

	vec3 biTangent = normalize(cross(normal, tangent));

	TexCoords = vec2(aTexcoord.xy);

	mat4 tangentBasis = mat4(
		tangent,	0.0,
		biTangent,	0.0,
		aNormal,	0.0,
		aPosition);

	TangentBasis = modelView * tangentBasis;
	gl_Position = projectionMatrix * TangentBasis[3];

	//mat4 transformation = projectionMatrix * viewMatrix * transformMatrix;
	//gl_Position = transformation * aPosition;
}