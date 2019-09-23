/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:50:30 by jloro             #+#    #+#             */
/*   Updated: 2019/09/23 11:58:27 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOMMANAGER_HPP
# define ROOMMANAGER_HPP

# include "GameObject.hpp"
# include "Model.hpp"
class RoomManager : public GameObject
{
	public:
		RoomManager(void);
		virtual~RoomManager();

		std::list<std::shared_ptr<GameObject>>	_rooms;

		void	Update();
		void	FixedUpdate();
	private:
		glm::vec3				_nextPos;
		glm::vec3				_nextRot;
		std::shared_ptr<Model>	_corridor;
		std::shared_ptr<Model>	_corner;

};

#endif
