#ifndef ARENDERER_HPP
# define ARENDERER_HPP

# include <iostream>
# include "Transform.hpp"
# include "Shader.hpp"
//# include "glm.hpp"
# include "gtc/matrix_transform.hpp"
# include "AComponent.hpp"

class ARenderer : public AComponent
{

public: 
/*	constructors / destrucors	*/
    ARenderer();
    ARenderer(std::shared_ptr<GameObject> obj);
    ARenderer(std::shared_ptr<Shader> shader, std::shared_ptr<GameObject> obj = nullptr);
    ARenderer(std::shared_ptr<Shader> shader, Transform trans, std::shared_ptr<GameObject> obj = nullptr);
    virtual ~ARenderer();
/*	public variables	*/
    Transform           transform;
/*	public functions	*/
    virtual glm::mat4       GetModelMatrix(void) const;
    virtual void            SetModelMatrix(glm::mat4 matrix);
    virtual void            UpdateMatrix(void);

    virtual std::shared_ptr<Shader> GetShader(void) const;
    //void                    Destroy(void);
    virtual void                    SetShader(std::shared_ptr<Shader>  shader);
    virtual void        Draw() const = 0;
protected:
    std::shared_ptr<Shader>    _shader;
    glm::mat4                  _modelMatrix;
};
#endif
