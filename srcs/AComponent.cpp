#include "AComponent.hpp"

AComponent::AComponent(std::shared_ptr<AGameObject> obj) 
{
    _gameObj.reset(obj);
}
AComponent::~AComponent() {}

std::shared_ptr<AGameObject>  AComponent::GetGameObj() const {return _gameObj;};