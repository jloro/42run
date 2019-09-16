#include "GameManager.hpp"
#include "Engine.hpp"
#include <cmath>

GameManager::GameManager() : _score(0), _obstacleSpeed(OBSTACLE_SPEED_DEFAULT), _canAdd(true)
{
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	_score = 0;
	_modelPillar.reset(new Model("ressources/obj/Pillar/LP_Pillar_Textured.obj"));
	srand(time(0));
	Transform trans(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f));
	for (int i = 0; i < 10; i++)
		_pillar.push_back(std::shared_ptr<MeshRenderer>(new MeshRenderer(_modelPillar, myShader, trans, false)));
	Engine42::Engine::AddRenderer(_pillar);
}

GameManager::~GameManager() {}

void	GameManager::Update()
{
	bool addNew = false;
	if (fmod(((float)SDL_GetTicks()) / 1000, .5) < 0.1 && _canAdd)
		addNew = true;
	else if (fmod(((float)SDL_GetTicks()) / 1000,  .5) > 0.1)
		_canAdd = true;
	for (auto it = _pillar.begin(); it != _pillar.end(); it++)
	{
		std::cout <<std::dynamic_pointer_cast<MeshRenderer>(*it)->IsRender() << " ";
		if (std::dynamic_pointer_cast<MeshRenderer>(*it)->IsRender())
		{
			if ((*it)->transform.position.z < -30.0f)
				std::dynamic_pointer_cast<MeshRenderer>(*it)->SetRender(false);
			(*it)->transform.position.z -= _obstacleSpeed * Engine42::Time::GetDeltaTime();
			(*it)->UpdateMatrix();
		}
		else if (addNew)
		{
			(*it)->transform.position.z = 30.0f;
			(*it)->transform.position.x = ROW_WIDTH * (rand() % 3 - 1);
			addNew = false;
			_canAdd = false;
			std::dynamic_pointer_cast<MeshRenderer>(*it)->SetRender(true);
			(*it)->UpdateMatrix();
		}
	}
	std::cout << std::endl;
}

void	GameManager::FixedUpdate()
{

}
