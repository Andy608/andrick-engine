#version 330 core

in vec3 lightColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(lightColor.xyz, 1.0);
}