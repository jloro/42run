#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 atexCoord;
layout (location = 3) in ivec4 aBoneIds;
layout (location = 4) in vec4 aWeights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gBones[100];

out vec2 TexCoords;
//out vec3 Normal;
//out vec3 Pos;

void main()
{
	mat4 boneTransform = gBones[aBoneIds[0]] * aWeights[0];
	boneTransform += gBones[aBoneIds[1]] * aWeights[1];
	boneTransform += gBones[aBoneIds[2]] * aWeights[2];
	boneTransform += gBones[aBoneIds[3]] * aWeights[3];

	TexCoords = atexCoord;
	//Normal = aNormal;
	//Pos = (projection * view * model * vec4(aPos, 1.0f)).xyz;
	gl_Position = projection * view * model * boneTransform * vec4(aPos, 1.0f);
}
