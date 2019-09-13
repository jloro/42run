#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include <iostream>
# include "Model.hpp"
# include "Camera.hpp"
# include "Transform.hpp"
# include "Time.hpp"
# include "ARenderer.hpp"
# include <memory>

class MeshRenderer : public ARenderer
{
public: 
/*	constructors / destrucors	*/
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, bool useNoise = false, 
    std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(nullptr));
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, 
    const Transform &transform, bool useNoise = false, std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(nullptr));
    MeshRenderer(const MeshRenderer & src); 
    virtual ~MeshRenderer(void); 

/*	public variables	*/
    Transform           transform;
/*	public functions	*/
    void                    Destroy(void);
	MeshRenderer &		    operator=(const MeshRenderer & rhs);
    virtual void        Draw() const;
protected:
    std::shared_ptr<Model>     _model;

private:
/*	private variables	*/
	bool				_noise;
	GLuint				_noiseID;
/*	private functions	*/
	void				InitNoiseText(void);
};
#endif

