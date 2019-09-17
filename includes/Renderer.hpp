#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <iostream>
# include "Transform.hpp"
# include "Shader.hpp"
//# include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Mesh.hpp"
class Renderer 
{

public: 
/*	constructors / destrucors	*/
    Renderer();
    Renderer(std::shared_ptr<Shader>  shader);
    Renderer(std::shared_ptr<Shader>  shader, Transform trans);
    virtual ~Renderer() {};
/*	public variables	*/
    Transform           transform;
	glm::vec3			min;
	glm::vec3			max;
/*	public functions	*/
    virtual glm::mat4       GetModelMatrix(void) const;
    virtual void            SetModelMatrix(glm::mat4 matrix);
    virtual void            UpdateMatrix(void);

    virtual std::shared_ptr<Shader> GetShader(void) const;
    //void                    Destroy(void);
    virtual void                    SetShader(std::shared_ptr<Shader>  shader);
    virtual void        Draw() const = 0;
	void				DrawCollider() const;
	void				InitCollider(glm::vec3 min, glm::vec3 max);
protected:
    std::shared_ptr<Shader>    _shader;
    std::shared_ptr<Shader>    _shaderCollider;
    std::shared_ptr<Mesh>    _meshCollider;
    glm::mat4                  _modelMatrix;

};
#endif
