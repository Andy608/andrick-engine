#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = /*vec4(TexCoords.xyz, 1.0);*/texture(skybox, TexCoords);
}