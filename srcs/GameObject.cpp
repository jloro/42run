#include "GameObject.hpp"
#include "AComponent.hpp"

GameObject::GameObject(void)
{
    _transform = std::shared_ptr<Transform>(new Transform());
}

GameObject::GameObject(Transform trans)
{
    _transform = std::shared_ptr<Transform>(new Transform(trans));
}

GameObject::~GameObject(void) {}

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