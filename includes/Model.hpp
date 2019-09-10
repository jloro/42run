/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:28:53 by jloro             #+#    #+#             */
/*   Updated: 2019/09/10 16:25:39 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_HPP
# define MODEL_HPP

# include "Mesh.hpp"
# include <assimp/scene.h>
# include <glm.hpp>
# include <gtx/quaternion.hpp>
# include <map>

# define ROTATION 0
# define SCALING 1
# define TRANSLATION 2

unsigned int TextureFromFile(const char *path, const std::string &directory);
class Model
{
	public:
/*  constructors / Destructor*/
		Model(void);
		Model(const char* path);
		Model(const Model & rhs);
		virtual~Model();
/*  public functions    */
		virtual void Draw(const std::shared_ptr<Shader>  shader);
        Model & operator=(const Model &rhs);
	protected:
/*  protected variables    */
		std::vector<Mesh>	_meshes;
		std::string			_dir;
		std::map<std::string, unsigned int>			_boneMap;
		std::vector<BoneInfo>	_boneInfo;
		glm::mat4				_globalTransform;

		const aiScene*			_scene;
/*  protected functions    */
		void					_LoadModel(std::string path);
		void					_ProcessNode(aiNode *node, const aiScene *scene);

		void					_LoadBones(aiMesh *mesh, std::vector<Vertex>& vertices);
		void					_AddBoneData(unsigned int id, float weight, Vertex& vertex);
		void					_BoneTransform(float timeInSecond);
		void					_ReadNodeHierarchy(float animationTime, const aiNode* node, const glm::mat4 parentTransform);
		aiQuaternion			_CalcInterpolatedRotation(float animationTime, const aiNodeAnim* nodeAnim) const;
		aiVector3D				_CalcInterpolatedScaling(float animationTime, const aiNodeAnim* nodeAnim) const;
		aiVector3D				_CalcInterpolatedTranslation(float animationTime, const aiNodeAnim* nodeAnim) const;
		unsigned int			_FindKeys(float animationTime, const aiNodeAnim* nodeAnim, int state) const;

		Mesh					_ProcessMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	_LoadMaterialTexture(aiMaterial *mat, aiTextureType type, eTextureType typeName);
		static Texture			_LoadSimpleTexture(eTextureType typeName, const std::string filename);
		static unsigned int 	_TextureFromFile(const char *path, const std::string &directory);
		static unsigned int 	_TextureFromFile(const std::string &filename) ;
		static std::string 		_GetFilename(const char *path, const std::string &directory);
};

#endif
