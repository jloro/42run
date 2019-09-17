#include "GameManager.hpp"
#include "Engine.hpp"
#include <cmath>

GameManager::GameManager(std::shared_ptr<Player> player) : _player(player), _score(0), _obstacleSpeed(OBSTACLE_SPEED_DEFAULT), _canAdd(true)
{
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	_score = 0;
	_modelPillar.reset(new Model("ressources/obj/box/Caixa.obj"));
	srand(time(0));
	Transform trans(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(14.0f, 14.0f, 14.0f));
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(trans));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(_modelPillar, myShader, std::shared_ptr<GameObject>(nullptr), false));
		Engine42::Engine::AddRenderer(renderer);
		go->AddComponent(renderer);
		_pillar.push_back(go);
	}
}

GameManager::~GameManager() {}

void	GameManager::Update()
{
	float timer = (rand() % 15 + 5) / 10;
	_CheckCollision();
	bool addNew = false;
	if (fmod(((float)SDL_GetTicks()) / 1000, timer) < 0.1 && _canAdd)
		addNew = true;
	else if (fmod(((float)SDL_GetTicks()) / 1000,  timer) > 0.1)
		_canAdd = true;
	for (auto it = _pillar.begin(); it != _pillar.end(); it++)
	{
		//std::cout <<std::dynamic_pointer_cast<MeshRenderer>(*it)->IsRender() << " ";
		if ((*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			if ((*it)->GetTransform()->position.z < -30.0f)
				(*it)->GetComponent<MeshRenderer>()->SetRender(false);
			(*it)->GetTransform()->position.z -= _obstacleSpeed * Engine42::Time::GetDeltaTime();
		}
		else if (addNew)
		{
			(*it)->GetTransform()->position.z = 30.0f;
			(*it)->GetTransform()->position.x = ROW_WIDTH * (rand() % 3 - 1);
			addNew = false;
			_canAdd = false;
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
		}
	}
	//std::cout << std::endl;
}

void	GameManager::FixedUpdate()
{
	
}

void	GameManager::_CheckCollision()
{
	glm::vec3 playerMinWorld = _player->GetComponent<ARenderer>()->min * _player->GetTransform()->scale + _player->GetTransform()->position;
	glm::vec3 playerMaxWorld = _player->GetComponent<ARenderer>()->max * _player->GetTransform()->scale + _player->GetTransform()->position;
	for (auto it = _pillar.begin(); it != _pillar.end(); it++)
	{
		glm::vec3 obsMaxWorldPos = (*it)->GetComponent<ARenderer>()->max * (*it)->GetTransform()->scale + (*it)->GetTransform()->position;
		glm::vec3 obsMinWorldPos = (*it)->GetComponent<ARenderer>()->min * (*it)->GetTransform()->scale + (*it)->GetTransform()->position;
		if ((*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			if (obsMinWorldPos.z < playerMaxWorld.z && obsMaxWorldPos.z > playerMaxWorld.z
					&& ((obsMinWorldPos.x > playerMinWorld.x && obsMinWorldPos.x < playerMaxWorld.x) || (obsMaxWorldPos.x > playerMinWorld.x && obsMaxWorldPos.x < playerMaxWorld.x))
					&& (playerMinWorld.y >= obsMinWorldPos.y && playerMinWorld.y < obsMaxWorldPos.y))
					exit(0);
		}
	}
}
