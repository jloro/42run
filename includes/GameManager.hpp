/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:46:50 by jloro             #+#    #+#             */
/*   Updated: 2019/09/24 13:38:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

# include "Model.hpp"
# include "Renderer.hpp"
# include <list>
# include "MeshRenderer.hpp"
# include "Player.hpp"
# include "Obstacle.hpp"
# include "RoomManager.hpp"

class GameManager : public GameObject
{
	public:
		GameManager(std::shared_ptr<Player> player);
		virtual~GameManager();

		virtual void	Update();
		virtual void	FixedUpdate();

		const static unsigned int	speedWorld;
	private:
		void					_CheckCollision();
		std::shared_ptr<Player>	_player;
		int						_score;
		std::shared_ptr<Model>	_modelPillar;
		std::shared_ptr<Obstacle>	_obstacle;
		std::shared_ptr<RoomManager>	_rooms;
};

#endif
