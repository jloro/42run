#include "RoomManager.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
RoomManager::RoomManager()
{
	_way = glm::vec3(1.0f);

	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	_corridor.reset(new Model("corridor/couloir.obj"));
	_corner.reset(new Model("corridor/corner.obj"));
	Transform trans(glm::vec3(40.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(20.0f, 20.0f, 40.0f), _transform);
	for (int i = 0; i < 10; i++)
	{
		trans.position.z = i * 40.0f;
		if (i == 9)
			trans.scale.x = 40.0f;
		std::shared_ptr<GameObject> go(new GameObject(trans));
		std::shared_ptr<ARenderer> renderer;
		if (i != 9)
			renderer.reset(new MeshRenderer(_corridor, myShader, std::shared_ptr<GameObject>(nullptr), true));
		else
			renderer.reset(new MeshRenderer(_corner, myShader, std::shared_ptr<GameObject>(nullptr), true));
		Engine42::Engine::AddRenderer(renderer);
		go->AddComponent(renderer);
		_rooms.push_back(go);
	}
}

RoomManager::~RoomManager() {}

bool		_sort(const std::shared_ptr<GameObject> first, const std::shared_ptr<GameObject> sec)
{
	return first->GetTransform()->position.z < sec->GetTransform()->position.z;
}

void	RoomManager::Update()
{
	//_transform->rotation.y += 2;
	//_transform->UpdateMatrix();
	for (auto it = _rooms.begin(); it != _rooms.end(); it++)
	{
		if ((*it)->GetTransform()->position.z < -50)
		{
			(*it)->GetTransform()->position.z = _rooms.back()->GetTransform()->position.z + 40.0f;
		}
		(*it)->GetTransform()->position.z -= 60 * Engine42::Time::GetDeltaTime();
		(*it)->GetTransform()->UpdateMatrix();
	}
	_rooms.sort(_sort);
}

void	RoomManager::FixedUpdate()
{

}
