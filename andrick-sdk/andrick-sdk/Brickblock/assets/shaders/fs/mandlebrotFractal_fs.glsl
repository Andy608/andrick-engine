#version 330 core

in vec2 out_textureCoords;

uniform sampler2D textureSampler;
uniform float time;

out vec4 FragColor;

void Mandlebrot();

void main()
{
	Mandlebrot();
}

void Mandlebrot()
{	
    vec2 z, c;
	int count = 0;
	float scale = 1.0;// / pow(2, time);
	const int ITER = 200;
	float er2 = 4.0;
	vec2 center = vec2(0.15, 0.65);
	
    c.x = 1.3333 * (out_textureCoords.x - 0.5) * scale - center.x;
    c.y = (out_textureCoords.y - 0.5) * scale - center.y;
	
    int i;
    z = c;
    for(i=0; i<ITER; i++) 
	{
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;
	
        if((x * x + y * y) > er2) break;
        z.x = x;
        z.y = y;
    }
	
	if (i == ITER)
	{
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	
	}
	else
	{
		FragColor = vec4(1.0 - count * scale);
	}
}