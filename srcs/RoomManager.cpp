#include "RoomManager.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include <gtx/rotate_vector.hpp>
RoomManager::RoomManager()
{
	_rotate = false;
	_nextPos = glm::vec3(0.0f, 0.0f, 0.0f);
	_nextRot = glm::vec3(0.0f, 0.0f, 0.0f);
	_way = glm::vec3(0.0f, 0.0f, 1.0f);

	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	_corridor.reset(new Model("corridor/couloir.obj"));
	_corner.reset(new Model("corridor/corner.obj"));
	Transform trans(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(40.0f, 20.0f, 40.0f), _transform);
	eTags	tag;
	srand(time(0));
	for (int i = 0; i < 30; i++)
	{
		float p = rand() % 100;
		if (p < 90)
		{
			tag = eTags::Corridor;
			trans.position += _way * 80.0f;
			trans.rotation = _nextRot;
		} else
		{
			tag = eTags::Corner;
			trans.position += _way * 160.0f;
			_nextRot += glm::vec3(0.0f, 90.0f, 0.0f);
			_way = glm::rotate(_way, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		std::shared_ptr<GameObject> go(new GameObject(trans, tag));
		if (p >= 90)
		{
			std::cout << glm::cross(_way)<< std::endl;
			if (glm::distance(_way, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f)
			{
				trans.position.x += 80;
			}
			else
			{
				;
			}
		}
		std::shared_ptr<ARenderer> renderer;
		if (p < 90)
		{
			renderer.reset(new MeshRenderer(_corridor, myShader, std::shared_ptr<GameObject>(nullptr), true));
		}
		else
		{
			renderer.reset(new MeshRenderer(_corner, myShader, std::shared_ptr<GameObject>(nullptr), true));
		}
		Engine42::Engine::AddRenderer(renderer);
		go->AddComponent(renderer);
		_rooms.push_back(go);
	}
	_way = glm::vec3(0.0f, 0.0f, 1.0f);
}

RoomManager::~RoomManager() {}

bool		_sort(const std::shared_ptr<GameObject> first, const std::shared_ptr<GameObject> sec)
{
	return first->GetTransform()->position.z < sec->GetTransform()->position.z;
}

void	RoomManager::Update()
{
	if (_rotate)
	{
		_transform->rotation.y -= 1;
		_transform->UpdateMatrix();
	}
	for (auto it = _rooms.begin(); it != _rooms.end(); it++)
	{
		if ((*it)->GetTransform()->position.z < 40 && (*it)->GetTag() == eTags::Corner)
		{
			if (_transform->rotation.y > -90)
			{
				_rotate = true;
				_way = glm::rotate(_way, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				std::cout <<_way << std::endl;
			}
			else
				_rotate = false;
			//(*it)->GetTransform()->position.z = _rooms.back()->GetTransform()->position.z + 80.0f;
		}
		//if (!_rotate)
			(*it)->GetTransform()->position -= _way * 40.0f * Engine42::Time::GetDeltaTime();
		(*it)->GetTransform()->UpdateMatrix();
	}
	_rooms.sort(_sort);
}

void	RoomManager::FixedUpdate()
{

}
