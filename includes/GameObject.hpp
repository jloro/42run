#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP
# include "SDL.h"
# include "Transform.hpp"
# include <memory>
# include <list>

class AComponent;

class GameObject
{
	public:
		GameObject(void);
		GameObject(Transform trans);
		// IGameObject(const IGameObject & src);
		virtual ~GameObject(void);
		virtual std::shared_ptr<Transform> GetTransform(void) const;
		void AddComponent(std::shared_ptr<AComponent> component);
		// IGameObject &	operator=(const IGameObject & rhs);

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
		// virtual int		Collide(IGameObject *other) = 0;
	protected:
		std::shared_ptr<Transform> _transform;
		std::list<std::shared_ptr<AComponent>> _components;
};
#endif
