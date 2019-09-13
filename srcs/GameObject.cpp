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
    if (find(_components.begin(), _components.end(), component) == _components.end())
    {
        _components.push_back(component);
        component->SetGameObject(this);
    }
}

GameObject::~GameObject(void) { }

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