#include "AGameObject.hpp"

AGameObject::AGameObject(void)
{
    _transform = std::shared_ptr<Tranform>(new Tranform());
}

AGameObject::AGameObject(Transform trans)
{
    _transform = std::shared_ptr<Tranform>(new Tranform(trans));
}

AGameObject::~AGameObject(void) {}

std::shared_ptr<Transform> AGameObject::GetTransform(void) const
{
    return _transform;
}