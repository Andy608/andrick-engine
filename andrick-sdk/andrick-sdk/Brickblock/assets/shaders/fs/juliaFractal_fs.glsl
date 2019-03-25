#version 330 core

in vec2 out_textureCoords;

uniform sampler2D texture0;
uniform sampler2D colRamp;

uniform float time;

out vec4 FragColor;

void Julia();

void main()
{
	Julia();
}

void Julia()
{
	//seed for fractal, determining bulbs, position, etc.
	vec2 seed = vec2(-0.624, 0.435);
	int count = 0;
	//scale of fractal
	float scale = 1.2;
	const int ITER = 200;
	float er2 = 4.0;

	vec2 z = (out_textureCoords * 2.0) * scale - scale;

	//vec2 seedOffset = seed;
	vec2 seedOffset = 0.6 * cos(seed + 0.1 * time) - sin(seed + 0.2 * time) * 0.15;

	for (int i = 0; i < ITER; i++)
	{
		float x = (z.x * z.x - z.y * z.y) + seedOffset.x;
		float y = (z.y * z.x + z.x * z.y) + seedOffset.y;

		count = i;
		if ((x * x + y * y) > er2) break;
		z.x = x;
		z.y = y;
	}

	if (count == ITER-1)
	{
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else
	{
		FragColor = texture(colRamp, vec2(count * 0.01, 0));
	}
}