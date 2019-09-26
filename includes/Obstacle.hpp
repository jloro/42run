/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:16:08 by jules             #+#    #+#             */
/*   Updated: 2019/09/26 11:48:28 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBSTACLE_HPP
# define OBSTACLE_HPP

# include "GameObject.hpp"
# include "Model.hpp"
# include "Shader.hpp"

class Obstacle : public GameObject
{
	public:
		Obstacle(void);
		virtual	~Obstacle();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
		std::list<std::shared_ptr<GameObject>>  _obstacles;

		void	Reset();
		void	Stop();
		void	Play();
	private:
		bool					_canAdd;
		std::list<std::shared_ptr<GameObject>>  _pillar;
		std::list<std::shared_ptr<GameObject>>  _jumpOver;
		bool					_stop;

		void					_AddObstacle(bool pillar);
};

#endif
