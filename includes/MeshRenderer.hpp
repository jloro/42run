#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include <iostream>
# include "Model.hpp"
# include "Camera.hpp"
# include "Transform.hpp"
# include "Time.hpp"
# include "Renderer.hpp"
# include <memory>

class MeshRenderer : public Renderer
{
public: 
/*	constructors / destrucors	*/
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, bool render = true); 
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, const Transform &transform, bool render = true); 
    MeshRenderer(const MeshRenderer & src); 
    virtual ~MeshRenderer(void); 

/*	public functions	*/
    void                    Destroy(void);
	MeshRenderer &		    operator=(const MeshRenderer & rhs);
    virtual void        Draw() const;
	bool				IsRender() const;
	void				SetRender(bool render);
protected:
    std::shared_ptr<Model>		_model;
	bool						_render;

};
#endif

