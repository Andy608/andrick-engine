#version 330 core

in vec2 out_textureCoords;

uniform sampler2D textureSampler;

out vec4 FragColor;

void main()
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
	
	//vec2 WIN_SIZE = vec2(1.0);
	//vec2 mv = WIN_SIZE / vec2(2.0);
	//vec2 z = mv + (4 * zoom / WIN_SIZE - 2) / zoom;


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
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		FragColor = vec4(1.0 - count * scale);
	}

    //FragColor = vec4(0, 1, 0, 1);//texture(textureSampler, out_textureCoords);
}