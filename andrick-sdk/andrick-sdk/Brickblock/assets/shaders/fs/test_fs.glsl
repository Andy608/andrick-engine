#version 330 core

in vec2 out_textureCoords;
in vec4 out_color;

uniform sampler2D texture0;

out vec4 FragColor;

void main()
{
	//FragColor = out_color;//vec4(0.0, 0.0, 0.0, 1.0);
	//FragColor = texture(textureSampler, vec2(1.0));
    FragColor = texture(texture0, out_textureCoords);
    //FragColor = vec4(out_textureCoords.xy, 1.0, 1.0);
}