#include "Player.hpp"
#include "Engine.hpp"
#include "gtx/compatibility.hpp"
Player::Player(std::shared_ptr<Model> character, std::shared_ptr<Shader> shader, Transform transform) : Renderer(shader, transform), _character(character), _jump(false)
{
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


void    Player::Update(void)
{
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_DOWN && transform.position.x > -25.0f)
		transform.position.x = glm::lerp(transform.position.x, -25.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_UP)
		transform.position.x = glm::lerp(transform.position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_DOWN && transform.position.x < 25.0f)
		transform.position.x = glm::lerp(transform.position.x, 25.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_UP)
		transform.position.x = glm::lerp(transform.position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_UP) == KEY_PRESS && _jump == false)
	{
		_jump = true;
		_jumpState = JUMPING;
	}
	if (_jump && _jumpState == JUMPING)
		transform.position.y = glm::lerp(transform.position.y, 20.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (_jump && transform.position.y > 19.9f)
		_jumpState = FALLING;
	if (_jump && _jumpState == FALLING)
		transform.position.y = glm::lerp(transform.position.y, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (_jump && transform.position.y < 0.1f)
		_jump = false;

	UpdateMatrix();
}
