/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:55:11 by jloro             #+#    #+#             */
/*   Updated: 2019/09/12 18:03:53 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "Renderer.hpp"
# include "IGameObject.hpp"
# include "Model.hpp"

enum eKeyState {
	KEY_PRESS, //key press during frame
	KEY_RELEASE, //key release during frame
	KEY_DOWN,
	KEY_UP

};
class Player : public Renderer, public Engine42::IGameObject
{
	public:
		Player(std::shared_ptr<Model> character, std::shared_ptr<Shader> shader, Transform trans);
		virtual~Player();

		virtual void        Draw() const;
		virtual void    Update(void);
		virtual void    FixedUpdate(void);
	private:
		std::shared_ptr<Model>	_character;
		void	_UpdateKeyboard(Uint8 scancode, const Uint8 *keys);

		std::map<Uint8, eKeyState>	_keyboard;
};

#endif
