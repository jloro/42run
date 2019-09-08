#ifndef BOXCOLLIDER_HPP
# define BOXCOLLIDER_HPP

# include <iostream>
# include "ACollider.hpp"

class BoxCollider : public ACollider
{

public: 
/*	constructors / destrucors	*/
    BoxCollider(std::shared_ptr<IGameObject> obj); 
    //BoxCollider(const BoxCollider & src); 
    virtual ~BoxCollider(void); 

/*	public variables	*/
/*	public functions	*/
	//BoxCollider &		operator=(const BoxCollider & rhs);
    virtual bool IsCollindingWith(ACollider &other) const;
private:
/*	private variables	*/
/*	private functions	*/

};

std::ostream &	operator<< (std::ostream & o, const BoxCollider & rhs);

#endif


#include "BoxCollider.hpp"
#include <iostream>

BoxCollider::BoxCollider(std::shared_ptr<IGameObject> obj) : ACollider(obj)
{
    
}

/*BoxCollider::BoxCollider(BoxCollider const & src) 
{
    *this = src;
    return;
}*/

BoxCollider::~BoxCollider(void)
{
    
}

/*BoxCollider &	BoxCollider::operator=(BoxCollider const & rhs)
{
    return *this;
}*/

bool IsCollindingWith(ACollider &other) const
{
    return false;
}