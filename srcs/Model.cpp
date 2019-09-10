/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:44:53 by jloro             #+#    #+#             */
/*   Updated: 2019/09/10 16:23:41 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Model.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
# ifndef STB_IMAGE_IMPLEMENTATION
#  define STB_IMAGE_IMPLEMENTATION
# endif
#include "stb_image.h"
#include <cmath>

Model::Model(void)
{
}

Model::Model(const char* path)
{
	_LoadModel(path);
	for (unsigned int i = 0; i < _meshes.size(); i++)
		_meshes[i].SendToOpenGL();
}
Model::Model(const Model &src)
{
	*this = src;
	for (unsigned int i = 0; i < _meshes.size(); i++)
		_meshes[i].SendToOpenGL();
}

Model::~Model() {}

void	Model::Draw(const std::shared_ptr<Shader>  shader)
{
	_BoneTransform(0);
	for (unsigned int i = 0; i < _meshes.size(); i++)
		_meshes[i].Draw(shader);
}
Model & Model::operator=(const Model &rhs)
{
	this->_dir = rhs._dir;
	this->_meshes = rhs._meshes;
	return *this;
}

glm::mat4	aiMat4ToGlmMat4(aiMatrix4x4 mat)
{
	glm::mat4	ret;

	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
			ret[i][j] = mat[i][j];
	}
	return ret;
}

void	Model::_LoadModel(std::string path)
{
	Assimp::Importer	import;
	_scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!_scene || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_scene->mRootNode)
		throw std::runtime_error(std::string("ERROR::ASSIMP::") + import.GetErrorString());
	if (_scene->HasAnimations())
	{
		std::cout << "Model:" << path << " has anim" << std::endl;
		std::cout << "nb anim: " <<_scene->mNumAnimations << std::endl;
		std::cout << "duration: "<<_scene->mAnimations[0]->mDuration<< std::endl;
		std::cout << "tick per sec: "<<_scene->mAnimations[0]->mTicksPerSecond<< std::endl;
	}

	_globalTransform = aiMat4ToGlmMat4(_scene->mRootNode->mTransformation.Inverse());

	_dir = path.substr(0, path.find_last_of('/'));
	_ProcessNode(_scene->mRootNode, _scene);

}

void	Model::_ProcessNode(aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		_meshes.push_back(_ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		_ProcessNode(node->mChildren[i], scene);
}

void	Model::_BoneTransform(float timeInSecond)
{
		std::cout << "nb anim: " <<_scene->mNumAnimations << std::endl;
		std::cout << "duration: "<<_scene->mAnimations[0]->mDuration<< std::endl;
		std::cout << "tick per sec: "<<_scene->mAnimations[0]->mTicksPerSecond<< std::endl;
	std::cout << "inBoneTransform"<< std::endl;
	//float ticksPerSecond = 25.0f;
	float ticksPerSecond = _scene->mAnimations[0]->mTicksPerSecond != 0 ? _scene->mAnimations[0]->mTicksPerSecond : 25.0f;
	std::cout << "inBoneTransform"<< std::endl;
	float timeInTicks = timeInSecond * ticksPerSecond;
	float animationTime = fmod(timeInTicks, _scene->mAnimations[0]->mDuration);

	_ReadNodeHierarchy(animationTime, _scene->mRootNode, glm::mat4(1.0f));
}

const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
{
	for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
		const aiNodeAnim* nodeAnim = pAnimation->mChannels[i];

		if (std::string(nodeAnim->mNodeName.data) == NodeName) {
			return nodeAnim;
		}
	}

	return NULL;
}

unsigned int	Model::_FindKeys(float animationTime, const aiNodeAnim* nodeAnim, int state) const
{
	if (state == ROTATION)
	{
		for (unsigned int i = 0 ; i < nodeAnim->mNumRotationKeys - 1 ; i++) {
			if (animationTime < (float)nodeAnim->mRotationKeys[i + 1].mTime) {
				return i;
			}
		}
	}
	else if (state == TRANSLATION)
	{
		for (unsigned int i = 0 ; i < nodeAnim->mNumPositionKeys - 1 ; i++) {
			if (animationTime < (float)nodeAnim->mPositionKeys[i + 1].mTime) {
				return i;
			}
		}
	}
	else
	{
		for (unsigned int i = 0 ; i < nodeAnim->mNumScalingKeys - 1 ; i++) {
			if (animationTime < (float)nodeAnim->mScalingKeys[i + 1].mTime) {
				return i;
			}
		}
	}
	return 0;
}
aiQuaternion	Model::_CalcInterpolatedRotation(float animationTime, const aiNodeAnim* nodeAnim) const
{
	if (nodeAnim->mNumRotationKeys == 1)
		return nodeAnim->mRotationKeys[0].mValue;

	unsigned int rotationIndex = _FindKeys(animationTime, nodeAnim, ROTATION);
	unsigned int nextRotationIndex = rotationIndex + 1;

	float delta = nodeAnim->mRotationKeys[nextRotationIndex].mTime - nodeAnim->mRotationKeys[rotationIndex].mTime;
	float factor = (animationTime - (float)nodeAnim->mRotationKeys[rotationIndex].mTime) / delta;

	const aiQuaternion start = nodeAnim->mRotationKeys[rotationIndex].mValue;
	const aiQuaternion end = nodeAnim->mRotationKeys[nextRotationIndex].mValue;

	aiQuaternion ret;
	aiQuaternion::Interpolate(ret, start, end, factor);
	return ret.Normalize();
}

aiVector3D		Model::_CalcInterpolatedTranslation(float animationTime, const aiNodeAnim* nodeAnim) const
{
	if (nodeAnim->mNumPositionKeys == 1)
		return nodeAnim->mPositionKeys[0].mValue;

	unsigned int positionIndex = _FindKeys(animationTime, nodeAnim, TRANSLATION);
	unsigned int nextPositionIndex = positionIndex + 1;

	float delta = nodeAnim->mPositionKeys[nextPositionIndex].mTime - nodeAnim->mPositionKeys[positionIndex].mTime;
	float factor = (animationTime - (float)nodeAnim->mPositionKeys[positionIndex].mTime) / delta;

	const aiVector3D start = nodeAnim->mPositionKeys[positionIndex].mValue;
	const aiVector3D end = nodeAnim->mPositionKeys[nextPositionIndex].mValue;

	aiVector3D	vec = end - start;
	return (start + vec * factor).Normalize();
}

aiVector3D		Model::_CalcInterpolatedScaling(float animationTime, const aiNodeAnim* nodeAnim) const
{
	if (nodeAnim->mNumScalingKeys == 1)
		return nodeAnim->mScalingKeys[0].mValue;

	unsigned int scalingIndex = _FindKeys(animationTime, nodeAnim, SCALING);
	unsigned int nextScalingIndex = scalingIndex + 1;

	float delta = nodeAnim->mScalingKeys[nextScalingIndex].mTime - nodeAnim->mScalingKeys[scalingIndex].mTime;
	float factor = (animationTime - (float)nodeAnim->mScalingKeys[scalingIndex].mTime) / delta;

	const aiVector3D start = nodeAnim->mScalingKeys[scalingIndex].mValue;
	const aiVector3D end = nodeAnim->mScalingKeys[nextScalingIndex].mValue;

	aiVector3D	vec = end - start;
	return (start + vec * factor).Normalize();
}

void	Model::_ReadNodeHierarchy(float animationTime, const aiNode* node, const glm::mat4 parentTransform)
{
	std::cout << "inReadNode"<< std::endl;
	std::string nodeName(node->mName.data);
	const aiAnimation* animation = _scene->mAnimations[0];
	const aiNodeAnim* nodeAnim = FindNodeAnim(animation, nodeName);

	if (nodeAnim)
	{
		aiVector3D	scale = _CalcInterpolatedScaling(animationTime, nodeAnim);
		glm::mat4	scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

		aiQuaternion	rotate = _CalcInterpolatedRotation(animationTime, nodeAnim);
		glm::mat4		rotateMat = aiMat4ToGlmMat4(aiMatrix4x4(rotate.GetMatrix()));

		aiVector3D	position = _CalcInterpolatedTranslation(animationTime, nodeAnim);
		glm::mat4	positionMat = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));


		glm::mat4	globalTransform = positionMat * rotateMat * scaleMat;

		if (_boneMap.find(nodeName) != _boneMap.end())
		{
			unsigned int boneIndex = _boneMap[nodeName];
			_boneInfo[boneIndex].finalTransMat = _globalTransform * globalTransform * _boneInfo[boneIndex].offsetMat;
		}

	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		_ReadNodeHierarchy(animationTime, node->mChildren[i], parentTransform);
}
void	Model::_LoadBones(aiMesh *mesh, std::vector<Vertex>& vertices)
{
	for (unsigned int i = 0; i < mesh->mNumBones; i++)
	{
		unsigned int boneIndex = 0;
		std::string boneName(mesh->mBones[i]->mName.data);

		if (_boneMap.find(boneName) == _boneMap.end())
		{
			boneIndex = _boneMap.size();
			BoneInfo bi;
			_boneInfo.push_back(bi);
		}
		else
			boneIndex = _boneMap[boneName];

		_boneMap[boneName] = boneIndex;
		_boneInfo[boneIndex].offsetMat = aiMat4ToGlmMat4(mesh->mBones[i]->mOffsetMatrix);

		for (unsigned int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
			_AddBoneData(i, mesh->mBones[i]->mWeights[j].mWeight, vertices[mesh->mBones[i]->mWeights[j].mVertexId]);
	}
}

void					Model::_AddBoneData(unsigned int id, float weight, Vertex& vertex)
{
	for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; i++)
	{
		if (vertex.weights[i] == -1)
		{
			vertex.weights[i] = weight;
			vertex.ids[i] = id;
			return;
		}
	}
}


Mesh	Model::_ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex>	vertices;
	std::vector<unsigned int>	faces;
	std::vector<Texture>	textures;

	std::cout <<  "Load mesh" << std::endl;
	//Get vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if (mesh->HasNormals())
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		else
			vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
		if (mesh->HasTextureCoords(0))
			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
		for (unsigned int j = 0; j < NUM_BONES_PER_VERTEX; j++)
		{
			vertex.weights[j] = -1;
			vertex.ids[j] = 0;
		}
		vertices.push_back(vertex);
	}
	//Get Bones
	if (mesh->HasBones())
	{
		_LoadBones(mesh, vertices);
	}
	//Get faces
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace	face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			faces.push_back(face.mIndices[j]);
	}
	if (scene->HasMaterials())
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = _LoadMaterialTexture(material, aiTextureType_DIFFUSE, Diffuse);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = _LoadMaterialTexture(material, aiTextureType_SPECULAR, Specular);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	//std::cout << "nb meshs" << std::endl;
	return Mesh(vertices, faces, textures);// I think this line force push to timeto openGl, cause it call the constructor 2 times
}

std::vector<Texture>	Model::_LoadMaterialTexture(aiMaterial *mat, aiTextureType type, eTextureType typeName)
{
	std::vector<Texture>	textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = _TextureFromFile(str.C_Str(), _dir);
		texture.type = typeName;
		textures.push_back(texture);
	}
	return textures;
}
Texture					Model::_LoadSimpleTexture(eTextureType typeName, const std::string path)
{
	Texture texture;
	texture.id = _TextureFromFile(path);
	texture.type = typeName;
	return texture;
}


std::string 			Model::_GetFilename(const char *path, const std::string &directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	return filename;
}
unsigned int 			Model::_TextureFromFile(const char *path, const std::string &directory)
{
	std::string filename = _GetFilename(path, directory);
	return (_TextureFromFile(filename));
	/*/std::string filename = std::string(path);
	  filename = directory + '/' + filename;*/
}
unsigned int 			Model::_TextureFromFile(const std::string &filename)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "failed to load texture " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
