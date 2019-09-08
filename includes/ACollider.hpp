#ifndef ACOLLIDER_HPP
# define ACOLLIDER_HPP

# include <iostream>
# include "AGameObject.hpp"
# include "AComponent.hpp"
# include <memory>

class ACollider : public AComponent
{

public: 
/*	constructors / destrucors	*/
    ACollider(std::shared_ptr<AGameObject> obj);
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