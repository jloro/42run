/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:16:08 by jules             #+#    #+#             */
/*   Updated: 2019/09/18 13:14:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBSTACLE_HPP
# define OBSTACLE_HPP

# include "GameObject.hpp"
# include "Model.hpp"
# include "Shader.hpp"

# define OBSTACLE_SPEED_DEFAULT 20

class Obstacle : public GameObject
{
	public:
		Obstacle(void);
		virtual	~Obstacle();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
		std::list<std::shared_ptr<GameObject>>  _obstacles;
	private:
		int						_obstacleSpeed;
		bool					_canAdd;
};

#endif
