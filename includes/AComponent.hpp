#ifndef ACOMPONENT_HPP
# define ACOMPONENT_HPP

# include <iostream>
# include "GameObject.hpp"
# include <memory>

class AComponent 
{
public: 
/*	constructors / destrucors	*/
    AComponent(std::shared_ptr<GameObject> obj);
    AComponent(GameObject *obj); 
    ~AComponent();

/*	public functions	*/
    virtual std::shared_ptr<GameObject>  GetGameObj() const;

protected:
    std::shared_ptr<GameObject> _gameObj;
};
#endif