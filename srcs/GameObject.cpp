#include "GameObject.hpp"
#include "AComponent.hpp"
#include <algorithm>

GameObject::GameObject(void) : _tag(eTags::Default)
{
    _transform = std::shared_ptr<Transform>(new Transform());
}

GameObject::GameObject(Transform trans) : _tag(eTags::Default)
{
    _transform = std::shared_ptr<Transform>(new Transform(trans));
}
GameObject::GameObject(Transform trans, eTags tag) : _tag(tag)
{
    _transform = std::shared_ptr<Transform>(new Transform(trans));
}
GameObject::GameObject(eTags tag) : _tag(tag)
{
    _transform = std::shared_ptr<Transform>(new Transform());
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

eTags	GameObject::GetTag() const { return _tag; }
void	GameObject::SetTag(eTags tag) { _tag = tag; }
