#ifndef ACOMPONENT_HPP
# define ACOMPONENT_HPP

# include <iostream>
# include "GameObject.hpp"
# include <memory>

class AComponent 
{
public: 
/*	constructors / destrucors	*/
    AComponent();
    AComponent(std::shared_ptr<GameObject> obj);
    virtual ~AComponent();
    void SetGameObject(std::shared_ptr<GameObject> obj);

/*	public functions	*/
    virtual std::shared_ptr<GameObject>  GetGameObj() const;

protected:
    std::shared_ptr<GameObject> _gameObj;
};
#endif