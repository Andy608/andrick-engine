#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normals;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformMatrix;
uniform float time;

out vec2 out_textureCoords;

void main()
{
	mat4 transformation = projectionMatrix * viewMatrix * transformMatrix;
	vec4 position = vec4(vertexPos, 1.0);

    gl_Position = transformation * position;
    out_textureCoords = texCoords;
}  