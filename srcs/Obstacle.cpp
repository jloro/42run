#include "Obstacle.hpp"
#include "Engine.hpp"
#include "BoxCollider.hpp"
#include "GameManager.hpp"

Obstacle::Obstacle() : _canAdd(true), _stop(false)
{
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	std::shared_ptr<Model>		modelServer(new Model("ressources/obj/server/server.obj"));
	std::shared_ptr<Model>		modelCroissant(new Model("ressources/obj/croissant/croissant.obj"));
	srand(time(0));
	Transform serverTransform(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f));
	Transform croissantTransform(glm::vec3(0.0f, 5.0f, 30.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f));
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(serverTransform));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(modelServer, myShader, nullptr, false));
		Engine42::Engine::AddRenderer(renderer);
		std::shared_ptr<ACollider> collider(new BoxCollider(go.get(), modelServer->GetMin(), modelServer->GetMax(), glm::vec3(1.0f), glm::vec3(0.0f), false));
		go->AddComponent(collider);
		go->AddComponent(renderer);
		_pillar.push_back(go);
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(croissantTransform));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(modelCroissant, myShader, nullptr, false));
		Engine42::Engine::AddRenderer(renderer);
		std::shared_ptr<ACollider> collider(new BoxCollider(go.get(), modelCroissant->GetMin(), modelCroissant->GetMax(), glm::vec3(1.0f), glm::vec3(0.0f), false));
		go->AddComponent(collider);
		go->AddComponent(renderer);
		_jumpOver.push_back(go);
	}
}

Obstacle::~Obstacle() {}

void	Obstacle::Stop()
{
	_stop = true;
}
void	Obstacle::Reset()
{
	_stop = false;
	_canAdd = true;
	_obstacles.clear();
	for (auto it = _pillar.begin(); it != _pillar.end(); it++)
	{
		(*it)->GetComponent<MeshRenderer>()->SetRender(false);
	}
}

void	Obstacle::Update()
{
	float timer = 2;
	if (fmod(((float)SDL_GetTicks()) / 1000, timer) < 0.1 && _canAdd)
	{
		_AddObstacle(static_cast<bool>(rand() % 2));
		_canAdd = false;
	}
	else if (fmod(((float)SDL_GetTicks()) / 1000,  timer) > 0.1)
		_canAdd = true;
	for (auto it = _obstacles.begin(); it != _obstacles.end(); it++)
	{
		//std::cout << (*it)->GetComponent<MeshRenderer>()->IsRender() << " ";
		if ((*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			if ((*it)->GetTransform()->position.z < -80.0f)
			{
				(*it)->GetComponent<MeshRenderer>()->SetRender(false);
				(*it)->GetComponent<MeshRenderer>()->Destroy();
				_obstacles.erase(it);
				continue;
			}
			if (!_stop)
				(*it)->GetTransform()->position.z -= GameManager::speedWorld * Engine42::Time::GetDeltaTime();
		}
	}
	//std::cout << std::endl;
}

void	Obstacle::FixedUpdate()
{

}

void	Obstacle::_AddObstacle(bool pillar)
{
	std::list<std::shared_ptr<GameObject>>::iterator it, end;
	if (pillar)
	{
		it = _pillar.begin();
		end = _pillar.end();
	}
	else
	{
		it = _jumpOver.begin();
		end = _jumpOver.end();
	}

	for (;it != end; it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			(*it)->GetTransform()->position.z = 500.0f;
			(*it)->GetTransform()->position.x = ROW_WIDTH * (rand() % 3 - 1);
			_canAdd = false;
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			_obstacles.push_back(*it);
			break;
		}
	}
}
