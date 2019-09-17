#include "Player.hpp"
#include "Engine.hpp"
#include "gtx/compatibility.hpp"
Player::Player(std::shared_ptr<Model> character, std::shared_ptr<Shader> shader, Transform transform) : GameObject(transform), _character(character), _jump(false)
{
	std::shared_ptr<ARenderer> render(new MeshRenderer(character, shader));
	Engine42::Engine::AddRenderer(render);
	AddComponent(render);
	render->InitCollider(_character->GetMin(), _character->GetMax(), glm::vec3(0.5f, 1.0f, 1.0f));
}

Player::~Player() {}


void    Player::FixedUpdate(void)
{
}


void    Player::Update(void)
{
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_DOWN && _transform->position.x > -ROW_WIDTH * 2.0f)
		_transform->position.x = glm::lerp(_transform->position.x, -ROW_WIDTH * 2.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_UP)
		_transform->position.x = glm::lerp(_transform->position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_DOWN && _transform->position.x < ROW_WIDTH * 2.0f)
		_transform->position.x = glm::lerp(_transform->position.x, ROW_WIDTH * 2.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_UP)
		_transform->position.x = glm::lerp(_transform->position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_UP) == KEY_PRESS && _jump == false)
	{
		_jump = true;
		_jumpState = JUMPING;
		_character->PauseAnimation();
	}
	if (_jump && _jumpState == JUMPING)
		_transform->position.y += JUMP_SPEED * Engine42::Time::GetDeltaTime();
	if (_jump && _transform->position.y > 40.0f)
		_jumpState = FALLING;
	if (_jump && _jumpState == FALLING)
		_transform->position.y -= JUMP_SPEED * Engine42::Time::GetDeltaTime();
	if (_jump && _transform->position.y <= 0.0f)
	{
		_character->PlayAnimation();
		_jump = false;
		_transform->position.y = 0.0f;
	}
}
