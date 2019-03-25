#version 330 core

//in vec2 out_textureCoords;
////in vec4 out_color;
//in vec3 out_normal;
//in vec3 out_fragPos;
//in vec3 out_lightPos;
//
//vec4 out_color;
//
//uniform sampler2D texture0;
//
////uniform vec3 modelColor;
//uniform vec3 lightColor;
//
//out vec4 FragColor;
//
//float AmbientStrength = 0.2;
//float SpecularStrength = 0.5;
//
//void main()
//{
//	//Ambient
//	vec3 ambientLight = AmbientStrength * lightColor;
//
//	//Diffuse
//	vec3 norm = normalize(out_normal);
//	vec3 vertexToLight = normalize(out_lightPos - out_fragPos);
//	float dotAngle = max(dot(norm, vertexToLight), 0.0);
//	vec3 diffuseLight = dotAngle * lightColor;
//	
//	//Specular
//	vec3 vertexToView = normalize(-out_fragPos);
//	vec3 reflection = reflect(-vertexToLight, norm);
//	float spec = pow(max(dot(vertexToView, reflection), 0.0), 32);
//	vec3 specular = SpecularStrength * spec * lightColor;
//
//	vec3 modelColor = texture(texture0, out_textureCoords).xyz;
//
//	vec3 result = (ambientLight + diffuseLight + specular) * modelColor;
//
//	out_color = vec4(result, 1.0);
//
//	FragColor = out_color;
//}


//Our varying data block that contains the light and texture data
in VB_BLOCK
{
	vec4 vPassTexcoord;
	float vPassAttenuation;

	vec3 vPassNormal;

	vec4 vPassEyeSpacePosition;
	vec4 vPassViewSpacePosition;

	vec4 vPassLightPos;

} vbBlock;

out vec4 rtFragColor;
//out vec4 rtNormal;
//out vec4 rtTexCoord;

//Calculate the diffuse coefficient for per vertex one light
float calcDiffuseCo(vec4 lightPosition);

//Calculate the specular coefficient for per vertex one light
float calcSpecularCo(vec4 lightPosition);

//calculates the diffuse and specular effects
vec4 calcDiffuse(float diffuseCo);
vec4 calcSpecular(float specularCo);

void main()
{
	//samples the diffuse and specular colors from the textures

	//variable to hold final phong model
	vec4 phong = vec4(0);


	//calculates the light direction from the object to the light
	vec4 lightDirection = normalize(vbBlock.vPassLightPos - vbBlock.vPassEyeSpacePosition);

	float diffuseCo = calcDiffuseCo(lightDirection);
	float specularCo = calcSpecularCo(lightDirection);

	//stores the final diffuse color
	vec4 phongDiffuse = calcDiffuse(diffuseCo);

	//stores the final specular color
	vec4 phongSpecular = calcSpecular(specularCo);

	//adds the diffuse and specular color, and applies the attenuation
	phong += (phongDiffuse + phongSpecular);
	
	
	rtFragColor = vec4(phong.xyz, 1.0);
	//rtNormal = vbBlock.vPassNormal * 0.5 + 0.5;
	//rtTexCoord = vbBlock.vPassTexcoord;

	rtFragColor = vec4(phongDiffuse.xyz, 1.0);
}

vec4 calcDiffuse(float diffuseCo)
{
	//calculates the diffuse from the coefficient, texture color, and light color
	vec4 diffuse = vec4(diffuseCo * vec3(1.0,1.0,1.0), 1.0);
	return diffuse;
}

vec4 calcSpecular(float specularCo)
{
	//calculates the specular from the coefficient, texture color, and light color
	vec4 specular = vec4(specularCo * vec3(1.0,1.0,1.0), 1.0);
	return specular;
}

float calcDiffuseCo(vec4 lightDirection)
{
	return max(dot(lightDirection, vec4(vbBlock.vPassNormal, 1.0)), 0.0);
}

float calcSpecularCo(vec4 lightDirection)
{
	vec4 reflectVec = normalize(2 * (dot(vec4(vbBlock.vPassNormal, 1.0), lightDirection)) * vec4(vbBlock.vPassNormal, 1.0) - lightDirection);//vec4(reflect(normalize(-lightDirection.xyz),  normalize(vbBlock.vPassNormal)), 1.0);
	
	float specularMax = max(0.0, dot(vbBlock.vPassViewSpacePosition, reflectVec));

	return pow(specularMax, 8);
}