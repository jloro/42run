/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ColliderRenderer.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:35:27 by jules             #+#    #+#             */
/*   Updated: 2019/09/18 13:50:07 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDERRENDERER_HPP
# define COLLIDERRENDERER_HPP

# include "ARenderer.hpp"
# include "ACollider.hpp"
# include "GameObject.hpp"

class ColliderRenderer : public ARenderer
{
	public:
		ColliderRenderer(GameObject* obj, ACollider* collider);
		virtual	~ColliderRenderer();

		virtual void        Draw() const;
	private:
		std::shared_ptr<Mesh>		_mesh;
		std::shared_ptr<Shader>		_shader;
		GameObject*					_go;
		ACollider*					_collider;
};

#endif
