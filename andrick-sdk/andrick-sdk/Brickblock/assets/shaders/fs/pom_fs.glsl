#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;
in vec3 Tangent;
in vec3 Normal;
in mat4 vPassTangentBasis;

//uniform sampler2D screenTexture;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{ 
	mat4 tangentBasis = mat4(
	normalize(vPassTangentBasis[0]), 
	normalize(vPassTangentBasis[1]),
	normalize(vPassTangentBasis[2]),
	vec4(0)
	);



	vec4 texThing = texture(texture1, TexCoords.xy);
	vec4 sample_nm = texture(texture1, TexCoords.xy) * 2.0 - 1.0;


	vec4 tangentTest = vec4(Tangent.xyz, 1.0);
	vec4 normalTest = vec4(Normal.xyz, 1.0);

	vec4 fragNrm_unit = tangentBasis * sample_nm;

	FragColor = fragNrm_unit;	
	FragColor = texThing;
	FragColor = vec4(1);
}