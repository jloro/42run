#include "ACollider.hpp"
#include <iostream>

/*ACollider::ACollider(void) 
{
    _gameObj = nullptr;
}*/

ACollider::ACollider(std::shared_ptr<AGameObject> obj) : ACollider(obj)
{
}

ACollider::~ACollider(void)
{
    
}
/*ACollider &	ACollider::operator=(ACollider const & rhs)
{
    return *this;
}*/