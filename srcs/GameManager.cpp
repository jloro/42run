#include "GameManager.hpp"
#include "Engine.hpp"
#include <cmath>
#include "ACollider.hpp"

const unsigned int	GameManager::speedWorld = 80.0f;
GameManager::GameManager(std::shared_ptr<Player> player) : _player(player), _score(0)
{
	_score = 0;
	_obstacle.reset(new Obstacle);
	Engine42::Engine::AddGameObject(_obstacle);
	_rooms.reset(new RoomManager);
	Engine42::Engine::AddGameObject(_rooms);
}

GameManager::~GameManager() {}

void	GameManager::Update()
{
	//for (auto it = _obstacle->_obstacles.begin(); it != _obstacle->_obstacles.end(); it++)
	//{
	//	if ((*it)->GetComponent<MeshRenderer>()->IsRender() && _player->GetComponent<ACollider>()->IsCollindingWith(*(*it)->GetComponent<ACollider>()))
			;//exit(0);
	//}
}

void	GameManager::FixedUpdate()
{
	
}

void	GameManager::_CheckCollision()
{
}
