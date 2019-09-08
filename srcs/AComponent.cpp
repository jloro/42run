#include "AComponent.hpp"

AComponent::AComponent(std::shared_ptr<GameObject> obj) 
{
    _gameObj = obj;
}
AComponent::AComponent(GameObject *obj) 
{
    _gameObj.reset(obj);
}
AComponent::~AComponent() {}

std::shared_ptr<GameObject>  AComponent::GetGameObj() const {return _gameObj;};