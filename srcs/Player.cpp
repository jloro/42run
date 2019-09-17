#include "Player.hpp"
#include "Engine.hpp"
#include "gtx/compatibility.hpp"
Player::Player(std::shared_ptr<Model> character, std::shared_ptr<Shader> shader, Transform transform) : Renderer(shader, transform), _character(character), _jump(false)
{
	InitCollider(_character->GetMin(), _character->GetMax(), glm::vec3(0.5f, 1.0f, 1.0f));
}

Player::~Player() {}


void        Player::Draw() const
{
    _shader->use();
    _shader->setMat4("view", Camera::instance->GetMatView());
    _shader->setMat4("projection", Camera::instance->GetMatProj());
    _shader->setMat4("model", _modelMatrix);
	_character->Draw(_shader);
    _shaderCollider->use();
    _shaderCollider->setMat4("view", Camera::instance->GetMatView());
    _shaderCollider->setMat4("projection", Camera::instance->GetMatProj());
    _shaderCollider->setMat4("model", _modelMatrixCollider);
	DrawCollider();
}
void    Player::FixedUpdate(void)
{
}


void    Player::Update(void)
{
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_DOWN && transform.position.x > -ROW_WIDTH * 2.0f)
		transform.position.x = glm::lerp(transform.position.x, -ROW_WIDTH * 2.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_UP)
		transform.position.x = glm::lerp(transform.position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_DOWN && transform.position.x < ROW_WIDTH * 2.0f)
		transform.position.x = glm::lerp(transform.position.x, ROW_WIDTH * 2.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_UP)
		transform.position.x = glm::lerp(transform.position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_UP) == KEY_PRESS && _jump == false)
	{
		_jump = true;
		_jumpState = JUMPING;
		_character->PauseAnimation();
	}
	if (_jump && _jumpState == JUMPING)
		transform.position.y += JUMP_SPEED * Engine42::Time::GetDeltaTime();
	if (_jump && transform.position.y > 40.0f)
		_jumpState = FALLING;
	if (_jump && _jumpState == FALLING)
		transform.position.y -= JUMP_SPEED * Engine42::Time::GetDeltaTime();
	if (_jump && transform.position.y <= 0.0f)
	{
		_character->PlayAnimation();
		_jump = false;
		transform.position.y = 0.0f;
	}

	UpdateMatrix();
}
