/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:50:30 by jloro             #+#    #+#             */
/*   Updated: 2019/09/19 18:57:38 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOMMANAGER_HPP
# define ROOMMANAGER_HPP

# include "GameObject.hpp"
# include "Room.hpp"
class RoomManager : public GameObject
{
	public:
		RoomManager(void);
		virtual~RoomManager();

		std::list<std::shared_ptr<GameObject>>	_rooms;

		void	Update();
		void	FixedUpdate();
	private:
		std::shared_ptr<Model>	_floor;
		std::shared_ptr<Model>	_wall;
		std::shared_ptr<Shader>	_shader;

		void _MakeRoom(glm::vec3 pos);
};

#endif
