#include "Room.hpp"
#include <iostream>

Room::Room(Transform trans) : GameObject(trans)
{}
Room::Room(Transform trans, std::vector<std::shared_ptr<GameObject>> walls) : GameObject(trans), _walls(walls)
{}

Room::Room(Room const & src) 
{
    *this = src;
    return;
}
Room::~Room(void)
{
    
}
void    Room::AddWall(std::vector<std::shared_ptr<GameObject>> walls)
{
    _walls.insert(_walls.end(), walls.begin(), walls.end());
}
void    Room::AddWall(std::shared_ptr<GameObject> wall)
{
    _walls.push_back(wall);
}
void Room::_Parenting()
{
    std::for_each(_walls.begin(), _walls.end(), [this](std::shared_ptr<GameObject> go) {go->GetTransform()->parent = this->_transform;});
}
void	Room::Update(void) {}
void	Room::FixedUpdate(void) {}
/*Room &	Room::operator=(Room const & rhs)
{
    return *this;
}

std::string const Room::toString(void) const
{
    
}

std::ostream &	operator<< (std::ostream & o, Room const & rhs)
{
    o << rhs.toString();
    return o;
}*/