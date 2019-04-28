#version 330 core

layout (location = 0)	in vec4 aPosition;
layout (location = 1)	in vec4 aTexcoord;
layout (location = 2)	in vec3 aNormal;

//TODO: We need to create them and pass them in.
//https://gamedev.stackexchange.com/questions/68612/how-to-compute-tangent-and-bitangent-vectors
//layout (location = 3)	in vec3 aTangent;
//layout (location = 4)	in vec3 aBitangent;

//uniform mat4 uMV, uP;
//uniform mat4 uAtlas;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformMatrix;

//out mat4 vPassTangentBasis;
//out vec4 vPassTexcoord;

void main()
{
//	mat4 tangentBasis = mat4(
//		aTangent,	0.0,
//		aBitangent,	0.0,
//		aNormal,	0.0,
//		aPosition);

//	vPassTangentBasis = uMV * tangentBasis;
//	vPassTexcoord = uAtlas * aTexcoord;	
//	gl_Position = uP * vPassTangentBasis[3];

	mat4 transformation = projectionMatrix * viewMatrix * transformMatrix;
	gl_Position = transformation * aPosition;
}