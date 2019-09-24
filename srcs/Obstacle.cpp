#include "Obstacle.hpp"
#include "Engine.hpp"
#include "BoxCollider.hpp"

Obstacle::Obstacle() : _obstacleSpeed(OBSTACLE_SPEED_DEFAULT), _canAdd(true)
{

	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	std::shared_ptr<Model> _modelPillar(new Model("ressources/obj/Pillar/LP_Pillar_Textured.obj"));
	srand(time(0));
	Transform trans(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(trans));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(_modelPillar, myShader, std::shared_ptr<GameObject>(nullptr), false));
		Engine42::Engine::AddRenderer(renderer);
		std::shared_ptr<ACollider> collider(new BoxCollider(go.get(), _modelPillar->GetMin(), _modelPillar->GetMax(), glm::vec3(1.0f), glm::vec3(0.0f), false));
		go->AddComponent(collider);
		go->AddComponent(renderer);
		_obstacles.push_back(go);
	}
}

Obstacle::~Obstacle() {}

void	Obstacle::Update()
{
	float timer = 4;
	bool addNew = false;
	if (fmod(((float)SDL_GetTicks()) / 1000, timer) < 0.1 && _canAdd)
		addNew = true;
	else if (fmod(((float)SDL_GetTicks()) / 1000,  timer) > 0.1)
		_canAdd = true;
	for (auto it = _obstacles.begin(); it != _obstacles.end(); it++)
	{
		std::cout << (*it)->GetComponent<MeshRenderer>()->IsRender() << " ";
		if ((*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			if ((*it)->GetTransform()->position.z < -30.0f)
				(*it)->GetComponent<MeshRenderer>()->SetRender(false);
			(*it)->GetTransform()->position.z -= _obstacleSpeed * Engine42::Time::GetDeltaTime();
		}
		else if (addNew)
		{
			(*it)->GetTransform()->position.z = 500.0f;
			(*it)->GetTransform()->position.x = ROW_WIDTH * (rand() % 3 - 1);
			addNew = false;
			_canAdd = false;
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
		}
	}
	std::cout << std::endl;
}

void	Obstacle::FixedUpdate()
{

}
