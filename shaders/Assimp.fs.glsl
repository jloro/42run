#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Pos;  

uniform sampler2D	texture_diffuse0;
uniform int			uHasTexture;
uniform vec3		uDiffuse;
uniform vec3		uAmbient;
uniform vec3		uSpecular;
uniform	vec3		uCamPos;

void main()
{
	vec4 textureColor = texture(texture_diffuse0, TexCoords);
	// ambient
	vec3 ambient =  uAmbient;

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = vec3(0.0f, 1.0f, 0.0f);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * uDiffuse;

	// specular
	vec3 viewDir = normalize(uCamPos - Pos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0f);
	vec3 specular = spec * uSpecular;  

	vec3 result = ambient + diffuse + specular;

	vec4 color = vec4(result, 1.0);
	float stepVal = step(uHasTexture, 0);
	FragColor =  stepVal * color + (1 - stepVal) * textureColor;
} 
