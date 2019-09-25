#include "GameManager.hpp"
#include "Engine.hpp"
#include <cmath>
#include "ACollider.hpp"

const unsigned int	GameManager::speedWorld = 80.0f;
std::shared_ptr<GameManager>	GameManager::instance = nullptr;

GameManager::GameManager(std::shared_ptr<Player> player) : _player(player), _score(0)
{
	if (instance == nullptr)
		instance = std::shared_ptr<GameManager>(this);
	_score = 0;
	_obstacle.reset(new Obstacle);
	Engine42::Engine::AddGameObject(_obstacle);
	_rooms.reset(new RoomManager);
	Engine42::Engine::AddGameObject(_rooms);
}

GameManager::~GameManager() {}

void	GameManager::Update()
{
	for (auto it = _obstacle->_obstacles.begin(); it != _obstacle->_obstacles.end(); it++)
	{
		if ((*it)->GetComponent<MeshRenderer>()->IsRender() && _player->GetComponent<ACollider>()->IsCollindingWith(*(*it)->GetComponent<ACollider>()))
		{
			Engine42::Engine::Clear();
			_Start();
			break;
		}
	}
}

void	GameManager::FixedUpdate()
{
	
}

void	GameManager::_Start()
{
	_rooms->Reset();
	Engine42::Engine::AddGameObject(_rooms);
	Engine42::Engine::AddGameObject(Camera::instance);
	_obstacle->Reset();
	Engine42::Engine::AddGameObject(_obstacle);
	_player->GetTransform()->position = glm::vec3(0.0f);
	Engine42::Engine::AddGameObject(_player);
	Engine42::Engine::AddRenderer(_player->GetComponent<MeshRenderer>());
	Engine42::Engine::AddGameObject(instance);
	/*
	std::shared_ptr<FpsDisplay> fps(new FpsDisplay);
	Engine42::Engine::AddUIElement(fps);
	std::shared_ptr<Camera> cam(new Camera(win.GetWidth(), win.GetHeight(), false));
	Engine42::Engine::AddGameObject(player);
	Engine42::Engine::AddGameObject(cam);
	*/
}
