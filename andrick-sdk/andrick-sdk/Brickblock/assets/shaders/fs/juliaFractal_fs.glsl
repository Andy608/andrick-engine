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
	vec2 seed = vec2(-0.624, 0.435);
	int count = 0;
	float scale = 0.1;
	const int ITER = 100;
	float er2 = 4.0;

	vec2 z = (out_textureCoords - 0.5);
	z *= 2.5;// / (float(uTime) * 0.02);

	float value = 1.0;
	float zoom = 2.0;

	for (int i = 0; i < ITER; i++)
	{
		float x = (z.x * z.x - z.y * z.y) + seed.x;
		float y = (z.y * z.x + z.x * z.y) + seed.y;

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
		FragColor = texture(colRamp, vec2(count * 0.01, 0)); //vec4(1.0 - count * scale);
	}
}