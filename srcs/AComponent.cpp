#include "AComponent.hpp"

AComponent::AComponent() : _gameObj(std::shared_ptr<GameObject>(nullptr))
{
}
AComponent::AComponent(std::shared_ptr<GameObject> obj) : _gameObj(obj)
{
}
/*AComponent::AComponent(GameObject *obj) 
{
    _gameObj.reset(obj);
}*/
    
AComponent::~AComponent() {std::cout << "component destructor " << std::endl;}

void    AComponent::SetGameObject(std::shared_ptr<GameObject> obj)
{
    _gameObj = obj;
    /*if (_gameObj != nullptr)
    {
        _gameObj->AddComponent(std::shared_ptr<AComponent>(this));
    }*/
}

std::shared_ptr<GameObject>  AComponent::GetGameObj() const {return _gameObj;};