/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsDisplay.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:29:20 by jules             #+#    #+#             */
/*   Updated: 2019/09/16 10:50:29 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPSDISPLAY_HPP
# define FPSDISPLAY_HPP

# include "GameObject.hpp"
# include "glm.hpp"

class FpsDisplay : public GameObject
{
	public:
		FpsDisplay(void);
		virtual	~FpsDisplay();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
	private:
		int				_nbFrame;
		float			_lastTime;
		int				_fps;

};

#endif
