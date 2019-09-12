#include "Player.hpp"
#include "Engine.hpp"
Player::Player(std::shared_ptr<Model> character, std::shared_ptr<Shader> shader, Transform transform) : Renderer(shader, transform), _character(character)
{

	_keyboard[SDL_SCANCODE_RIGHT] = KEY_UP;
	_keyboard[SDL_SCANCODE_LEFT] = KEY_UP;
}

Player::~Player() {}


void        Player::Draw() const
{
    _shader->use();
    _shader->setMat4("view", Camera::instance->GetMatView());
    _shader->setMat4("projection", Camera::instance->GetMatProj());
    _shader->setMat4("model", _modelMatrix);
	_character->Draw(_shader);
}
void    Player::FixedUpdate(void)
{

}

void	Player::_UpdateKeyboard(Uint8 scancode, const Uint8 *keys)
{
	if (keys[scancode] && _keyboard[scancode] == KEY_UP)
		_keyboard[scancode] = KEY_PRESS;
	else if (keys[scancode] && _keyboard[scancode] == KEY_PRESS)
		_keyboard[scancode] = KEY_DOWN;
	else if (!keys[scancode] && _keyboard[scancode] == KEY_DOWN)
		_keyboard[scancode] = KEY_RELEASE;
	else if (!keys[scancode] && _keyboard[scancode] == KEY_RELEASE)
		_keyboard[scancode] = KEY_UP;
}

void    Player::Update(void)
{
	const Uint8 	*keys = Engine42::Engine::GetKeyInput();

	_UpdateKeyboard(SDL_SCANCODE_RIGHT, keys);
	_UpdateKeyboard(SDL_SCANCODE_LEFT, keys);
	if (_keyboard[SDL_SCANCODE_RIGHT] == KEY_PRESS && transform.position.x > -5.0f)
		transform.position.x -= 5.0f;
	if (_keyboard[SDL_SCANCODE_RIGHT] == KEY_RELEASE)
		transform.position.x += 5.0f;
	if (_keyboard[SDL_SCANCODE_LEFT] == KEY_PRESS && transform.position.x < 5.0f)
		transform.position.x += 5.0f;
	if (_keyboard[SDL_SCANCODE_LEFT] == KEY_RELEASE)
		transform.position.x -= 5.0f;
	UpdateMatrix();
}
