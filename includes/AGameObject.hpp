#ifndef AGAMEOBJECT_HPP
# define AGAMEOBJECT_HPP
# include "SDL.h"
# include "Transform.hpp"
# include "AComponent.hpp"
# include <memory>
# include <list>

class AGameObject
{
	public:
		AGameObject(void);
		AGameObject(Transform trans);
		// IGameObject(const IGameObject & src);
		virtual ~AGameObject(void) {}
		virtual std::shared_ptr<Transform> GetTransform(void) const;
		// IGameObject &	operator=(const IGameObject & rhs);

		virtual void	Update(void) = 0;
		virtual void	FixedUpdate(void) = 0;
		// virtual int		Collide(IGameObject *other) = 0;
	protected:
		std::shared_ptr<Transform> _transform;
		std::list<shared_ptr<AComponent>> _components;
};
#endif
