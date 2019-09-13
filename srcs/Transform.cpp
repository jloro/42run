#include "Transform.hpp"
#include <sstream>

Transform::Transform()
{
    _Initialize(glm::vec3(0, 0, 0), glm::vec3(0,0,0), glm::vec3(1,1,1));
}

Transform::Transform(Transform const & src) 
{
    *this = src;
    return;
}

Transform::~Transform(void) {}

Transform &	Transform::operator=(Transform const & rhs)
{
    position = rhs.position;
    rotation = rhs.rotation;
    scale = rhs.scale;
    return *this;
}
    Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent)
    {
        _Initialize(pos, rot, scale, parent);
    }
    Transform::Transform(glm::vec3 pos, glm::vec3 scale, std::shared_ptr<Transform> parent)
    {
        _Initialize(pos, glm::vec3(0,0,0), scale, parent);
    }
    Transform::Transform(glm::vec3 pos, std::shared_ptr<Transform> parent)
    {
        _Initialize(pos, glm::vec3(0,0,0), glm::vec3(1,1,1), parent);
    }
    void    Transform::_Initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent)
    {
        this->position = pos;
        this->rotation = rot;
        this->scale = scale;
        this->parent = parent;
    }


std::string const Transform::toString(void) const
{
    std::stringstream ss("pos { ");
    ss << position << " } rot { ";
    ss << rotation << " } scale { ";
    ss << scale << " }";
    return ss.str();
}

std::ostream &	operator<< (std::ostream & o, Transform const & rhs)
{
    o << rhs.toString();
    return o;
}