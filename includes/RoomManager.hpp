/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:50:30 by jloro             #+#    #+#             */
/*   Updated: 2019/09/25 13:02:29 by jloro            ###   ########.fr       */
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

		glm::vec3	rotate(glm::vec3& vec, float angle, glm::vec3 normal);

		std::list<std::shared_ptr<GameObject>>	corners;
		std::list<std::shared_ptr<GameObject>>	corridors;

		const static unsigned int	maxRooms;

		void	Reset();
	private:
		glm::vec3		_nextPos;
		glm::vec3				_nextRot;
		glm::vec3				_wayPlacement;
		glm::vec3				_way;
		bool	_rotate;
		std::shared_ptr<Model>	_corridor;
		std::shared_ptr<Model>	_corner;
		unsigned int			_nbRooms;
		int	_rotationMax;
		float	_rotateWay;

		bool					_cornerSpawned;

		void					_AddCorridor();
		void					_AddCorner(bool left);

		void					_Init();

};

#endif
