#ifndef ROOM_HPP
# define ROOM_HPP

# include <iostream>
# include "Terrain.hpp"
# include "GameObject.hpp"

class Room : public GameObject
{

public: 
/*	constructors / destrucors	*/
    Room(Transform trans); 
    Room(Transform trans, std::vector<std::shared_ptr<GameObject>> walls); 
    Room(const Room & src); 
    virtual ~Room(void); 

/*	public variables	*/
/*	public functions	*/
	//Room &		operator=(const Room & rhs);

    virtual void	Update(void);
	virtual void	FixedUpdate(void);
    void AddWall(std::vector<std::shared_ptr<GameObject>> walls);
    void AddWall(std::shared_ptr<GameObject> wall);
    //std::string const	toString(void) const;

private:
/*	private variables	*/
    std::vector<std::shared_ptr<GameObject>> _walls;
/*	private functions	*/
    void    _Parenting(void);

};

//std::ostream &	operator<< (std::ostream & o, const Room & rhs);

#endif