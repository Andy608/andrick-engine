#version 330 core
//layout (location = 0) in vec3 vertexPos;
////layout (location = 1) in vec2 texCoords;
//layout (location = 1) in vec3 normals;
//
//uniform mat4 viewMatrix;
//uniform mat4 projectionMatrix;
//uniform mat4 transformMatrix;
//uniform mat3 normalMatrix;
//uniform float time;
//
//uniform vec3 lightPos;
//
//out vec3 out_normal;
//out vec3 out_fragPos;
//out vec3 out_lightPos;
//
//float Speed = 0.5;
//
//void main()
//{
//	//Position
//	mat4 viewTransform = viewMatrix * transformMatrix;
//
//	vec4 viewPos = viewTransform * vec4(vertexPos, 1.0);
//
//    gl_Position = projectionMatrix * viewPos;
//
//	//Lighting
//
//	out_normal = normalMatrix * normals;
//	out_fragPos = viewPos.xyz;
//	out_lightPos = (viewMatrix * vec4(lightPos, 1.0)).xyz;
//} 

//layout (location = 0) in vec4 aPosition;
//layout (location = 2) in vec4 aNormal;
//layout (location = 8) in vec4 aTexcoord;

////////////////////////////////////////////

//layout (location = 0) in vec3 vertexPos;
//layout (location = 1) in vec2 texCoords;
//layout (location = 2) in vec3 normals;
//
////The amount of lights in the scene.
//
////Our transform uniform variables
//uniform mat4 viewMatrix;
//uniform mat4 transformMatrix;
//uniform mat4 projectionMatrix;
//uniform mat3 normalMatrix;
//
////Our light uniform variables
//uniform vec3 lightPos;
//uniform float lightSz;
//
////Our varying data block that contains the light and texture data
//out VB_BLOCK
//{
//	vec4 vPassTexcoord;
//	float vPassAttenuation;
//
//	//Scene Data
//	vec3 vPassNormal;
//
//	vec4 vPassEyeSpacePosition;
//	vec4 vPassViewSpacePosition;
//
//	vec4 vPassLightPos;
//
//} vbBlock;
//
////Calculate the attenuation coefficient for per vertex one light
//float calcAttenuation();
//
////View space transforms
//vec4 eyeSpaceNormal;
//
//void main()
//{
//	mat4 uMV = viewMatrix * transformMatrix;
//	mat4 uP = projectionMatrix;
//
//	vbBlock.vPassLightPos = uMV * vec4(lightPos, 1.0);
//
//	//transforms object space to eye-space
//	vbBlock.vPassEyeSpacePosition = uMV * vec4(vertexPos, 1.0);
//
//	//transforms object normal space to eye normal space
//
//	//transforms eye space to view space
//	vbBlock.vPassViewSpacePosition = normalize(-vbBlock.vPassEyeSpacePosition);
//
//	//transforms eye space to clip space	
//	vec4 clipSpace = uP * vbBlock.vPassEyeSpacePosition;
//
//	vbBlock.vPassTexcoord = vec4(texCoords, 1.0, 1.0);
//
//	//runs for each light
//
//	vbBlock.vPassAttenuation = calcAttenuation();
//
//	vbBlock.vPassNormal = normalize(normalMatrix * normals);
//
//	gl_Position = clipSpace;
//}
//
//float calcAttenuation()
//{
//	//calculates light based on distance from object
//	float attenuation = 1.0 / (1.0 + lightSz * pow(distance(vbBlock.vPassLightPos, vbBlock.vPassEyeSpacePosition), 2));
//
//	return attenuation;
//}

//Lighting help from https://learnopengl.com/Lighting/Basic-Lighting/
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords; 

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main()
{
	FragPos = vec3(transformMatrix * vec4(aPos, 1.0));
	Normal = normalMatrix * aNormal;
	TexCoords = aTex;

	gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}