#ifndef ARENDERER_HPP
# define ARENDERER_HPP

# include <iostream>
# include "Transform.hpp"
# include "Shader.hpp"
# include "Mesh.hpp"
# include "AComponent.hpp"

class ARenderer : public AComponent
{

public: 
/*	constructors / destrucors	*/
    ARenderer();
    ARenderer(std::shared_ptr<GameObject> obj);
    ARenderer(std::shared_ptr<Shader> shader, GameObject *obj = nullptr);
    ARenderer(std::shared_ptr<Shader> shader, std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(nullptr));
    virtual ~ARenderer();
/*	public variables	*/
/*	public functions	*/

    virtual std::shared_ptr<Shader> GetShader(void) const;
    //void                    Destroy(void);
    virtual void                    SetShader(std::shared_ptr<Shader>  shader);
    virtual void        Draw() const = 0;
	void				DrawCollider() const;
	void				InitCollider(glm::vec3 min, glm::vec3 max, glm::vec3 scale);
	glm::vec3			scaleCollider;
	glm::vec3			min;
	glm::vec3			max;
protected:
    std::shared_ptr<Shader>    _shader;
	std::shared_ptr<Shader>    _shaderCollider;
	std::shared_ptr<Mesh>    _meshCollider;
	glm::mat4                  _modelMatrixCollider;
};
#endif
