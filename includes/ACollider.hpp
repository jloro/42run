#ifndef ACOLLIDER_HPP
# define ACOLLIDER_HPP

# include <iostream>
# include "GameObject.hpp"
# include "AComponent.hpp"
# include <memory>
# include "Mesh.hpp"

class ACollider : public AComponent
{

public: 
/*	constructors / destrucors	*/
    ACollider(GameObject *obj, glm::vec3 min, glm::vec3 max, glm::vec3 scale, glm::vec3 offset, bool showMesh);
    //ACollider(GameObject *obj);

    //ACollider(const ACollider & src); 
    virtual ~ACollider(void); 
/*	public variables	*/
/*	public functions	*/
	//ACollider &		operator=(const ACollider & rhs);
    virtual bool IsCollindingWith(ACollider &other);

	glm::vec3	center; //offset with pos of transform
	glm::vec3	size;

private:
/*	private variables	*/
/*	private functions	*/

};

#endif
