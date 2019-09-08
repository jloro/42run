#ifndef ACOMPONENT_HPP
# define ACOMPONENT_HPP

# include <iostream>
# include "AGameObject.hpp"
# include <memory>

class AComponent 
{
public: 
/*	constructors / destrucors	*/
    AComponent(std::shared_ptr<AGameObject> obj);
    ~AComponent();

/*	public functions	*/
    virtual std::shared_ptr<AGameObject>  GetGameObj() const;

protected:
    std::shared_ptr<AGameObject> _gameObj;
};
#endif