#ifndef ACOLLIDER_HPP
# define ACOLLIDER_HPP

# include <iostream>
# include "GameObject.hpp"
# include "AComponent.hpp"
# include <memory>

class ACollider : public AComponent
{

public: 
/*	constructors / destrucors	*/
    ACollider(std::shared_ptr<GameObject> obj);
    //ACollider(GameObject *obj);

    //ACollider(const ACollider & src); 
    virtual ~ACollider(void); 
/*	public variables	*/
/*	public functions	*/
	//ACollider &		operator=(const ACollider & rhs);
    virtual bool IsCollindingWith(ACollider &other) const = 0;

private:
    ACollider(void); 
/*	private variables	*/
/*	private functions	*/

};

#endif