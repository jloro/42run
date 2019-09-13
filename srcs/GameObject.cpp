#include "GameObject.hpp"
#include "AComponent.hpp"
#include <algorithm>

GameObject::GameObject(void)
{
    _transform = std::shared_ptr<Transform>(new Transform());
}

GameObject::GameObject(Transform trans)
{
    _transform = std::shared_ptr<Transform>(new Transform(trans));
}
void GameObject::AddComponent(std::shared_ptr<AComponent> component)
{
    std::cout << "add component called" << std::endl;

    if (find(_components.begin(), _components.end(), component) == _components.end())
    {
        std::cout << "push back" << std::endl;
        _components.push_back(component);
    }

}
/*void GameObject::AddComponent(std::shared_ptr<AComponent> component)
{
    _components.push_back(component);
}*/

GameObject::~GameObject(void) { std::cout << "destructor GO"<<std::endl;}

std::shared_ptr<Transform> GameObject::GetTransform(void) const
{
    return _transform;
}
void	GameObject::Update(void)
{
}
void	GameObject::FixedUpdate(void)
{
}