#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;
in mat4 TangentBasis;

//uniform sampler2D screenTexture;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec2 range;

void main()
{ 
	//vec2 uRange = vec2(0.9925f, 0.9975f);

	//How to get out of tangent space to view space (calculated in vertex shader)
	mat4 tangentBasis = mat4(
		normalize(TangentBasis[0]),
		normalize(TangentBasis[1]),
		normalize(TangentBasis[2]),
		vec4(0.0)
	);

	//Pom
	vec4 viewPos_unit = normalize(vec4(TangentBasis[3].xyz, 1.0));
	vec3 rayDir_tan;
	rayDir_tan.x = dot(tangentBasis[0], viewPos_unit);
	rayDir_tan.y = dot(tangentBasis[1], viewPos_unit);
	rayDir_tan.z = dot(tangentBasis[2], viewPos_unit);

	//Height map original vs max height values
	vec3 c_original_texCoord = vec3(TexCoords.xy, 1.0);
	vec3 c_far = c_original_texCoord - rayDir_tan / rayDir_tan.z;
	vec3 c_original_texCoord_prime = mix(c_far, c_original_texCoord, range.y);
	vec3 c_far_prime = mix(c_far, c_original_texCoord, range.x);

//	vec3 c_current_texCoord;
	vec3 c_current_texCoord_prime;

	int numSamples = 100, i;
	float dt = 1.0 / float(numSamples), t = 0.0;
//	float n = float(numSamples);
//	float dt = (uRange.y - uRange.x) / n; //Mapped range
	float h = range.y; //max

	for (i = 0; i < numSamples; ++i)
	{
		//c_current_texCoord = mix(c_original_texCoord, c_far, h);
		c_current_texCoord_prime = mix(c_original_texCoord_prime, c_far_prime, t);
		h = c_current_texCoord_prime.z;

		vec4 height = texture(texture1, c_current_texCoord_prime.xy);
		float height_prime = mix(range.x, range.y, height.r);

		//We are past the fake surface!
		if (height_prime > h)
		{
			break;
		}

		t += dt;
	}

	//Find where intersects

	vec2 texcoord = c_current_texCoord_prime.xy;

	//rtFragColor = vec4(rayDir_tan, 1.0);
	//rtFragColor.a = 1.0;
	//return;


	//rtFragColor = vec4(vec3( float(i) * dt ), 1.0);
	//return;

		
	vec4 sample_dm = texture(texture0, TexCoords.xy);
	vec4 sample_hm = texture(texture1, texcoord.xy);
	vec4 sample_nm = texture(texture2, texcoord.xy) * 2.0 - 1.0;

	//vec4 fragNrm_unit = tangentBasis[2];
	vec4 fragNrm_unit = tangentBasis * sample_nm;
	vec4 lightVec = vec4(0.0, 0.0, 1.0, 0.0);

	float kd = dot(fragNrm_unit, lightVec);
	kd = max(kd, 0.0);

	FragColor = vec4(kd);// * sample_dm;
	//FragColor = fragNrm_unit;
	FragColor.a = 1.0;
	//FragColor = sample_nm;
	//FragColor = vec4(0.0, 0.0, 1.0, 1.0);

	// DUMMY OUTPUT: standard normal blue
	//rtNormal = vec4(0.5, 0.5, 1.0, 1.0);
}